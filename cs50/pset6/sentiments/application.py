from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
from analyzer import Analyzer
from termcolor import colored


app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # TODO
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
    positive, negative, neutral = 0.0, 0.0, 0.0
    # analyze text
    for i in range (0, 200):
        score = analyzer.analyze(tweets[i])
        if score > 0.0:
            print(colored(str(tweets[i]), "green"))
            positive=positive+1
        elif score < 0.0:
            print(colored(str(tweets[i]), "red"))
            negative=negative+1
        else:
            print(colored(str(tweets[i]), "yellow"))
            neutral=neutral+1

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
