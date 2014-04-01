import java.util.*;

import java.util.Set;

import java.util.TreeSet;

public class Ass5 { public List union(List list1, List list2) { Set set = new HashSet();

set.addAll(list2);
set.addAll(list1);
return new ArrayList<T>(set);
}

public static List prime(List arr)

{

int n, status = 1, num = 3;

Scanner in = new Scanner(System.in);

System.out.println("Enter the number of prime numbers you want");

n = in.nextInt();

if (n >= 1) { System.out.println("First "+n+" prime numbers are :-");

 System.out.println(2);
arr.add(2);

}

for ( int count = 2 ; count <=n ; ) {

 for ( int j = 2 ; j <= Math.sqrt(num) ; j++ )

 {
    if ( num%j == 0 )

    {
       status = 0;

       break;

    }

 }

 if ( status != 0 )

 {

    System.out.println(num);

arr.add(num);

    count++;

 }
 status = 1;

 num++;
}

return arr;

}

public static int findnum(List al) {

int k,s,i=1;

Scanner in = new Scanner(System.in);

System.out.println("Enter k: ");

k = in.nextInt();

List m=al;

System.out.println("Enter seed: ");

s = in.nextInt();

//List[] g = new ArrayList[20];

//ArrayList[] g = (ArrayList[])Array.newInstance(ArrayList.class,
20);

//List> group = new ArrayList>(20);

ArrayList[] g = new ArrayList[20];

for (int ii=0;ii<20;ii++) {

g[ii] = new ArrayList();

}

g[0].add(s);

do {

    System.out.println("lol");

        List<Integer> list1=g[i-1];

int temp=(Integer)g[i-1].get(i-1);

        List<Integer> list2=new ArrayList<Integer>();

for(Integer item : m) {

    list2.add(item*temp) ;
}
System.out.println(new Ass5().union(list1, list2));

 g[i].union(list1, list2);

        //G[i] = G[i-1] + (M * G[i-1].get(i-1)); // ‘+’ means set union

        i++;

 }
while( ((Integer)g[i-1].get(k)) > ((Integer)m.get(0)*(Integer)g[i-1].get(i-1)) );

return (Integer)g[i].get(k);

}

public static void main(String args[]) {

List al = new ArrayList();

prime(al);

int res=0;

res=findnum(al);

System.out.println("Contents of al: " + al);

System.out.println("Contents of al[0]: " + al.get(0));

System.out.println("ok ");

}

}