import nltk
import cs50

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.wordpos = set()
        self.wordneg = set()
        with open(positives, "r") as file_pos:
            for line in file_pos:
                if line.startswith(";"):
                    continue
                line = line.rstrip("\n")
                self.wordpos.add(line)
        with open (negatives, "r") as file_neg:
            for line in file_neg:
                if line.startswith(";"):
                    continue
                line = line.rstrip("\n")
                self.wordneg.add(line)            
        file_pos.close()
        file_neg.close()


    def analyze(self, text):
        text.strip()
        text.lower()
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens=tokenizer.tokenize(text) 
        score =0;
        lenght=len(tokens)
        for i in range (0, lenght):
            if tokens[i].lower() in self.wordpos:
                score=score+1
            if tokens[i].lower() in self.wordneg:
                score=score-1
        return score
