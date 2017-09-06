from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from flask_sqlalchemy import SQLAlchemy

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    row = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    rows=db.execute("SELECT * FROM buy WHERE username =:username ", username=row[0]["username"])
    total_price=0
    for r in range (len(rows)):
        total_price=total_price+float(rows[r]["total"]) 
    return render_template("index.html", stocks = rows, cash=row[0]["cash"], total=float(row[0]["cash"])+total_price)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        if request.form["symbol"]=="":
            return apology("symbol is missing")
        symbol=request.form["symbol"]
        shares1=int(request.form["shares1"])
        if shares1 < 0:
            return apology("shares is not positive integer")
        quote1=lookup(symbol)
        price = float( quote1['price'])
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        bought=db.execute("SELECT * FROM buy WHERE username =:username ", username=rows[0]["username"]);
        total=shares1*price
        if rows[0]["cash"]<(int(quote1['price']) * shares1):
            return apology("It's not enough money")
        for i in range(len(bought)):
            if symbol==bought[i]['symbol'] and float(quote1['price'])==float(bought[i]['price']):
                db.execute("UPDATE buy SET shares= :shares, total= :total WHERE username= :username", username=rows[0]["username"], shares=int(bought[i]['shares'])+shares1, total=float(bought[i]['total'])+total)
                db.execute("UPDATE users SET cash= :cash WHERE username= :username", cash=int(int(rows[0]["cash"])-int(quote1['price'])*shares1), username=rows[0]["username"])
                db.execute("INSERT INTO sold (username, symbol, name, price, shares, total, condition) VALUES (:username, :symbol, :name, :price, :shares, :total, :condition)", username=rows[0]["username"], symbol = quote1['symbol'], name = quote1['name'], price =quote1['price'], shares=shares1, total=total, condition="bought")
                return redirect(url_for("index"))
                
        if price:
            db.execute("INSERT INTO buy(username, symbol, name, price, shares, total) VALUES (:username, :symbol, :name, :price, :shares, :total)", username=rows[0]["username"], symbol = quote1['symbol'], name = quote1['name'], price =quote1['price'], shares=shares1, total=total)
            db.execute("UPDATE users SET cash= :cash WHERE username= :username", cash=int(int(rows[0]["cash"])-int(quote1['price'])*shares1), username=rows[0]["username"])
            db.execute("INSERT INTO sold (username, symbol, name, price, shares, total, condition) VALUES (:username, :symbol, :name, :price, :shares, :total, :condition)", username=rows[0]["username"], symbol = quote1['symbol'], name = quote1['name'], price =quote1['price'], shares=shares1, total=total, condition="bought")
    else:
        return render_template("buy.html")
    return redirect(url_for("index"))

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    row = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    rows=db.execute("SELECT * FROM sold WHERE username =:username ", username=row[0]["username"])
    return render_template("history.html", stocks = rows)
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if request.form["cname"]=="":
            return apology("quote is missing")
        symbol=request.form["cname"]
        quote1=lookup(symbol)
        if quote1:
            return render_template("quoted.html", name = quote1['name'], price = quote1['price'], symbol=quote1['symbol'])
        else:
            return apology("quote is missing")
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        if request.form["username"]=="":
            return apology("Missing username")
        if request.form["password"]=="":
            return apology("Missing password")
        if request.form["password"] != request.form["confirmation"]:
            return apology("wrong confirmation")
        
        """result=db.execute("SELECT * FROM users WHERE username = :username", username=request.form["username"])
        if result:
            return apology("This name is already exist")"""
        
        password = pwd_context.hash(request.form["password"])
        row=db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form["username"], hash=password)
        if row:
            result=db.execute("SELECT * FROM users WHERE username = :username", username=request.form["username"])
            session["user_id"] = result[0]["id"]
            return redirect(url_for("index"))
        else:
            return apology("This name is already exist")
    else:
        return render_template("register.html")
        
@app.route("/cpas", methods=["GET", "POST"])
@login_required
def cpas():
    """Register user."""
    if request.method == "POST":
        if request.form["npassword"]=="":
            return apology("Missing new password")
        if request.form["npassword"] != request.form["confirmation"]:
            return apology("wrong confirmation")
        print("good")
        npassword = pwd_context.hash(request.form["npassword"])
        print("good")
        row = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        if row:
            result=db.execute("UPDATE users SET hash = :hash WHERE username= :username", hash=npassword, username=row[0]["username"])
            return redirect(url_for("index"))
        else:
            return apology("You can't do this")
    else:
        return render_template("cpas.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        if request.form["symbol"]=="":
            return apology("symbol is missing")
        symbol=request.form["symbol"]
        shares1=int(request.form["shares1"])
        if shares1 < 0:
            return apology("shares is not positive integer")
        quote1=lookup(symbol)
        price = float( quote1['price'])
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        bought=db.execute("SELECT * FROM buy WHERE username =:username ", username=rows[0]["username"]);
        
        total=shares1*price
        
        for i in range(len(bought)):
            if int(bought[i]["shares"])< int(shares1):
                return apology("It's not enough stock")
            if symbol==bought[i]['symbol']:
                shares=int(bought[i]['shares'])-shares1
                if shares is 0:
                    db.execute("DELETE FROM buy WHERE symbol= :symbol", symbol = bought[i]['symbol'])
                else:
                    db.execute("UPDATE buy SET shares= :shares, total= :total WHERE username= :username", username=rows[0]["username"], shares=shares, total=(float(bought[i]['total'])-total))
                db.execute("UPDATE users SET cash= :cash WHERE username= :username", cash=int(int(rows[0]["cash"])+int(quote1['price'])*shares1), username=rows[0]["username"])
                db.execute("INSERT INTO sold (username, symbol, name, price, shares, total, condition) VALUES (:username, :symbol, :name, :price, :shares, :total, :condition)", username=rows[0]["username"], symbol = quote1['symbol'], name = quote1['name'], price =quote1['price'], shares=shares1, total=total, condition="sold")
                return redirect(url_for("index"))
            return apology("the symbol is missing")
    else:
        return render_template("sell.html")
    return redirect(url_for("index"))
