class Bar(object):
    def __init__(self, name):
        self.name = name

class Thing(object):
    def __init__(self):
        self.bars = []

    def create_bar(self, name):
        self.bars.append(Bar(name=name))
        return self.bars[-1]

foo = Thing()
bar = foo.create_bar(name='test')
bar.name = 'hello'
print(foo.bars[-1].name)
print(bar.name)
