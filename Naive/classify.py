"""
Assignment 3. Implement a Multinomial Naive Bayes classifier for spam filtering.
You'll only have to implement 3 methods below:
train: compute the word probabilities and class priors given a list of documents labeled as spam or ham.
classify: compute the predicted class label for a list of documents
evaluate: compute the accuracy of the predicted class labels.
"""

from collections import defaultdict
import glob
import math
import os



class Document(object):
    """ A Document. Do not modify.
    The instance variables are:
    filename....The path of the file for this document.
    label.......The true class label ('spam' or 'ham'), determined by whether the filename contains the string 'spmsg'
    tokens......A list of token strings.
    """

    def __init__(self, filename=None, label=None, tokens=None):
        """ Initialize a document either from a file, in which case the label
        comes from the file name, or from specified label and tokens, but not
        both.
        """
        if label: # specify from label/tokens, for testing.
            self.label = label
            self.tokens = tokens
        else: # specify from file.
            self.filename = filename
            self.label = 'spam' if 'spmsg' in filename else 'ham'
            self.tokenize()

    def tokenize(self):
        self.tokens = ' '.join(open(self.filename).readlines()).split()


class NaiveBayes(object):

    def get_word_probability(self, label, term):
        """
        Return Pr(term|label). This is only valid after .train has been called.
        Params:
          label: class label.
          term: the term
        Returns:
          A float representing the probability of this term for the specified class.
        >>> docs = [Document(label='spam', tokens=['a', 'b']), Document(label='spam', tokens=['b', 'c']), Document(label='ham', tokens=['c', 'd'])]
        >>> nb = NaiveBayes()
        >>> nb.train(docs)
        >>> nb.get_word_probability('spam', 'a')
        0.25
        >>> nb.get_word_probability('spam', 'b')
        0.375
        """
        ###TODO
        pass
        t=0
        if label=='ham':
            
            return self.hamcnd[term]
        else:
            
            return self.spamcnd[term]
       

    def get_top_words(self, label, n):
        """ Return the top n words for the specified class, using the odds ratio.
        The score for term t in class c is: p(t|c) / p(t|c'), where c'!=c.
        Params:
          labels...Class label.
          n........Number of values to return.
        Returns:
          A list of (float, string) tuples, where each float is the odds ratio
          defined above, and the string is the corresponding term.  This list
          should be sorted in descending order of odds ratio.
        >>> docs = [Document(label='spam', tokens=['a', 'b']), Document(label='spam', tokens=['b', 'c']), Document(label='ham', tokens=['c', 'd'])]
        >>> nb = NaiveBayes()
        >>> nb.train(docs)
        >>> nb.get_top_words('spam', 2)
        [(2.25, 'b'), (1.5, 'a')]
        """
        ###TODO
        pass
        dictw={}
        if label=='ham':
            for m in self.tknham.keys():
                dictw[m]=self.get_word_probability('ham', m)/self.get_word_probability('spam', m)
        else:
            for m in self.tknspam.keys():
                dictw[m]=self.get_word_probability('spam', m)/self.get_word_probability('ham', m)
        return (list(zip(([m[1] for m in sorted(dictw.items(),key=lambda x:x[1],reverse=True)[:n]]),
                  ([m[0] for m in sorted(dictw.items(),key=lambda x:x[1],reverse=True)[:n]]))))
    def train(self, documents):
        """
        Given a list of labeled Document objects, compute the class priors and
        word conditional probabilities, following Figure 13.2 of your
        book. Store these as instance variables, to be used by the classify
        method subsequently.
        Params:
          documents...A list of training Documents.
        Returns:
          Nothing.
        """
        ###TODO
        pass
        self.dic ={}
        clsdoc={}
        self.hamcnd={}
        self.spamcnd={}
        cnt=0;
        clsdoc['ham']=0
        clsdoc['spam']=0
        self.prior={}
        self.prior['ham']=0
        self.prior['spam']=0
        self.tknham={}
        self.tknspam={}
        self.spm=0;
        self.ham=0;
        for obj in documents:
            for wrd in obj.tokens:
                if wrd in self.dic.keys():
                    self.dic[wrd]=self.dic[wrd]+1
                else:
                    self.dic[wrd]=1
                if obj.label=='ham':
                    self.ham=self.ham+1
                    if wrd in self.tknham.keys():
                        self.tknham[wrd]=self.tknham[wrd]+1
                    else:
                        self.tknham[wrd]=1
                    if wrd not in self.tknspam.keys():
                        self.tknspam[wrd]=0
                else:
                    self.spm=self.spm+1
                    if wrd in self.tknspam.keys():
                        self.tknspam[wrd]=self.tknspam[wrd]+1
                    else:
                        self.tknspam[wrd]=1
                    if wrd not in self.tknham.keys():
                        self.tknham[wrd]=0
            cnt=cnt+1
            clsdoc[obj.label]=clsdoc[obj.label]+1
        for m in ['spam','ham']:
            self.prior[m]=clsdoc[m]/cnt
        for m in self.dic:
            self.hamcnd[m]=(self.tknham[m]+1)/(len(self.dic)+self.ham)
            self.spamcnd[m]=(self.tknspam[m]+1)/(len(self.dic)+self.spm)
        
    def classify(self, documents):
        """ Return a list of strings, either 'spam' or 'ham', for each document.
        Params:
          documents....A list of Document objects to be classified.
        Returns:
          A list of label strings corresponding to the predictions for each document.
        """
        ###TODO
        pass
        scrham=0
        scrspm=0
        lis=[]
        for m in range(len(documents)):
            scrham=math.log10(self.prior['ham'])
            scrspm=math.log10(self.prior['spam'])
            for n in documents[m].tokens:
                if n in self.hamcnd.keys():
                    scrham=scrham+math.log10(self.get_word_probability('ham', n))
                
                if n in self.spamcnd.keys():
                    scrspm=scrspm+math.log10(self.get_word_probability('spam', n))
                
            if scrspm>scrham:
                lis.append('spam')
            else:
                lis.append('ham')
        return lis
def evaluate(predictions, documents):
    """ Evaluate the accuracy of a set of predictions.
    Return a tuple of three values (X, Y, Z) where
    X = percent of documents classified correctly
    Y = number of ham documents incorrectly classified as spam
    X = number of spam documents incorrectly classified as ham
    Params:
      predictions....list of document labels predicted by a classifier.
      documents......list of Document objects, with known labels.
    Returns:
      Tuple of three floats, defined above.
    """
    ###TODO
    pass
    cnt=0
    per=0
    nh=0
    ns=0
    for m in range(len(documents)):
        if documents[m].label==predictions[m]:
            cnt=cnt+1
        else:
            if documents[m].label=='ham':
                nh=nh+1
            else:
                ns=ns+1
    per=cnt/len(documents)
    return per,nh,ns
def main():
    """ Do not modify. """
    if not os.path.exists('train'):  # download data
       from urllib.request import urlretrieve
       import tarfile
       urlretrieve('http://cs.iit.edu/~culotta/cs429/lingspam.tgz', 'lingspam.tgz')
       tar = tarfile.open('lingspam.tgz')
       tar.extractall()
       tar.close()
    train_docs = [Document(filename=f) for f in glob.glob("train/*.txt")]
    print('read', len(train_docs), 'training documents.')
    nb = NaiveBayes()
    nb.train(train_docs)
    test_docs = [Document(filename=f) for f in glob.glob("test/*.txt")]
    print('read', len(test_docs), 'testing documents.')
    predictions = nb.classify(test_docs)
    results = evaluate(predictions, test_docs)
    print('accuracy=%.3f, %d false spam, %d missed spam' % (results[0], results[1], results[2]))
    print('top ham terms: %s' % ' '.join('%.2f/%s' % (v,t) for v, t in nb.get_top_words('ham', 10)))
    print('top spam terms: %s' % ' '.join('%.2f/%s' % (v,t) for v, t in nb.get_top_words('spam', 10)))

if __name__ == '__main__':
    main()
