struct Foo {};

int foo(Foo* foo, int (Foo::*ptr)(int))
{
  return (foo->*ptr)(5);
}

/*
define i32 @_Z3fooP3FooMS_FiiE(%struct.Foo* %foo, { i32, i32 }* byval nocapture readonly align 4) #0 {
entry:
  %ptr = load { i32, i32 }* %0, align 4
  %ptr.fca.0.extract = extractvalue { i32, i32 } %ptr, 0
  %ptr.fca.1.extract = extractvalue { i32, i32 } %ptr, 1
  %1 = getelementptr inbounds %struct.Foo* %foo, i32 %ptr.fca.1.extract, i32 0
  %this.adjusted = bitcast i8* %1 to %struct.Foo*
  %2 = and i32 %ptr.fca.0.extract, 1
  %memptr.isvirtual = icmp eq i32 %2, 0
  br i1 %memptr.isvirtual, label %memptr.nonvirtual, label %memptr.virtual

memptr.virtual:                                   ; preds = %entry
  %3 = bitcast i8* %1 to i8**
  %memptr.vtable = load i8** %3, align 4
  %4 = add i32 %ptr.fca.0.extract, -1
  %5 = getelementptr i8* %memptr.vtable, i32 %4
  %6 = bitcast i8* %5 to i32 (%struct.Foo*, i32)**
  %memptr.virtualfn = load i32 (%struct.Foo*, i32)** %6, align 4
  br label %memptr.end

memptr.nonvirtual:                                ; preds = %entry
  %memptr.nonvirtualfn = inttoptr i32 %ptr.fca.0.extract to i32 (%struct.Foo*, i32)*
  br label %memptr.end

memptr.end:                                       ; preds = %memptr.nonvirtual, %memptr.virtual
  %7 = phi i32 (%struct.Foo*, i32)* [ %memptr.virtualfn, %memptr.virtual ], [ %memptr.nonvirtualfn, %memptr.nonvirtual ]
  %call = tail call i32 %7(%struct.Foo* %this.adjusted, i32 5)
  ret i32 %call
}
*/