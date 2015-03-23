package main

type Foo struct {}

func (f Foo) test() {}

type Bar struct {}

func (b Bar) test() {}

func main() {
    var i interface { test() } = Foo {}
	i.test()
	i = Bar {}
	i.test()
}