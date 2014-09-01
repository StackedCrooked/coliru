#!/usr/bin/python

class Element:
    re = 0

    def assign(self, r):
        self.re = r
        
    def __repr__(self):
        return str(self.re)
        

Element.re = 10         # set class variable
e = Element()
e.assign(42)            # set instance variable

print Element.re, e.re
