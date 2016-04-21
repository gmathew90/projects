"""
Assignment 5: K-Means. See the instructions to complete the methods below.
"""

from collections import Counter,defaultdict
import gzip
import math

import numpy as np


class KMeans(object):

    def __init__(self, k=2):
        """ Initialize a k-means clusterer. Should not have to change this."""
        self.k = k

    def cluster(self, documents, iters=10):
        """
        Cluster a list of unlabeled documents, using iters iterations of k-means.
        Initialize the k mean vectors to be the first k documents provided.
        After each iteration, print:
        - the number of documents in each cluster
        - the error rate (the total Euclidean distance between each document and its assigned mean vector), rounded to 2 decimal places.
        See Log.txt for expected output.
        The order of operations is:
        1) initialize means
        2) Loop
          2a) compute_clusters
          2b) compute_means
          2c) print sizes and error """
        ###TODO
        pass
        self.mn_doc=[]
        
        for m in range(self.k):
            self.mn_doc.append(documents[m])
            
        for it in range(iters):
            self.compute_clusters(documents)
            print ([len(m) for m in self.clstr.values()])
            
            self.compute_means()
            print ("%.2f" %self.error(documents))
    def compute_means(self):
        """ Compute the mean vectors for each cluster (results stored in an
        instance variable of your choosing).
        """
        ###TODO
        pass
        
        self.mn_doc=[]
        for m in range(len(self.clstr)):
            c=Counter()
            for n in self.clstr[m]:
                for a in n:
                    c.update({a:n[a]})
            
            for n in c.keys():
                c[n]=c[n]/len(self.clstr[m])
            self.mn_doc.append(c)
        self.mean_vctr=[]
        for m in self.mn_doc:
            self.mean_vctr.append(float(self.sqnorm(m)))
       
    def compute_clusters(self, documents):
        """ Assign each document to a cluster. (Results stored in an instance
        variable of your choosing).
        """
        ###TODO
        pass
        self.mean_vctr=[]
        self.dtls=defaultdict(list)
        self.clstr=defaultdict(list)
        for m in self.mn_doc:
            
            self.mean_vctr.append(float(self.sqnorm(m)))
        for n in documents:
            tmp=[[j,self.distance(n,self.mn_doc[j],self.mean_vctr[j])] for j in range(len(self.mn_doc))]
            
            self.dtls[min(tmp,key= lambda x:x[1])[0]].append([min(tmp,key= lambda x:x[1])[1],n])
            self.clstr[min(tmp,key= lambda x:x[1])[0]].append(n)
    def sqnorm(self, d):
        """ Return the vector length of a dictionary d, defined as the sum of
        the squared values in this dict. """
        ###TODO
        pass
        t=0
        for m in d.values():
                t=t+(m*m)
        return (t)
    def distance(self, doc, mean, mean_norm):
        """ Return the Euclidean distance between a document and a mean vector.
        See here for a more efficient way to compute:
        http://en.wikipedia.org/wiki/Cosine_similarity#Properties"""
        ###TODO
        pass
        c=0
        for key in doc.keys():
            if key in mean:
                c=c+(doc[key]*mean[key])
        
        return float(math.sqrt(self.sqnorm(doc)+mean_norm-(2.0*c)))
        
       
    def error(self, documents):
        """ Return the error of the current clustering, defined as the total
        Euclidean distance between each document and its assigned mean vector."""
        ###TODO
        pass
        err=0
        for m in range(len(self.clstr)):
            for n in self.clstr[m]:
                err=err+self.distance(n,self.mn_doc[m],self.mean_vctr[m])
        return err
        
    def print_top_docs(self, n=10):
        """ Print the top n documents from each cluster. These are the
        documents that are the closest to the mean vector of each cluster.
        Since we store each document as a Counter object, just print the keys
        for each Counter (sorted alphabetically).
        Note: To make the output more interesting, only print documents with more than 3 distinct terms.
        See Log.txt for an example."""
        ###TODO
        pass
        for a in range(self.k):
            print("CLUSTER "+str(a))
            
            t=[m for m in self.dtls[a] if len(m[1])>3]
            k=sorted(t, key = lambda x : x[0])[:n]
            for m in k:
                bu=""
                for a in (sorted(m[1].keys())):
                    bu=bu+a+" "
                print(bu)
def prune_terms(docs, min_df=3):
    """ Remove terms that don't occur in at least min_df different
    documents. Return a list of Counters. Omit documents that are empty after
    pruning words.
    >>> prune_terms([{'a': 1, 'b': 10}, {'a': 1}, {'c': 1}], min_df=2)
    [Counter({'a': 1}), Counter({'a': 1})]
    """
    ###TODO
    pass
    c=Counter()
    li=[]
    lis=[]
    for m in docs:
        for n in m:
            c.update({n:1})

    for m in c:
        if c[m]>=min_df:
            li.append(m)

    for m in docs:
        c=Counter()
        for n in m:
            if n in li:
                c.update({n:m[n]})
        if (len(c)!=0):        
            lis.append(c)
    return lis

def read_profiles(filename):
    """ Read profiles into a list of Counter objects.
    DO NOT MODIFY"""
    profiles = []
    with gzip.open(filename, mode='rt', encoding='utf8') as infile:
        for line in infile:
            profiles.append(Counter(line.split()))
    return profiles


def main():
    profiles = read_profiles('profiles.txt.gz')
    print('read', len(profiles), 'profiles.')
    profiles = prune_terms(profiles, min_df=2)
    km = KMeans(k=10)
    km.cluster(profiles, iters=20)
    km.print_top_docs()

if __name__ == '__main__':
    main()
