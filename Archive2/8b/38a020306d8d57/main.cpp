list1 = [1, 2, 3, 4]
thing1 = [1]
thing2 = [2]
thing3 = [3]
thing4 = [4]
all_things = thing1 + thing2 + thing3 + thing4

relation_holds = True
for it1, it2 in zip(list1, all_things):
    print "List1:\t",it1
    print "List2:\t",it2
    print ""
    if it1 * 2 != it2:
        relation_holds = False

