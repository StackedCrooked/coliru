  #include <Password.h>
     
    Password password = Password( "1234" );
     
    void setup(){
      Serial.begin(9600);
     
       <Password.h>.append('1');//add 1 to the guessed password
       <Password.h>.append('2');//add 2 to the guessed password
       <Password.h>.append('3');//add 3 to the guessed password
       <Password.h>.append('4');//add 4 to the guessed password
      //should print true, since 1234 == 1234
      Serial.println(  <Password.h>.evaluate()?"true":"false" );
     
       <Password.h>.reset(); //reset the guessed password to NULL
      //should print false, since 1234 != NULL
      Serial.println(  <Password.h>.evaluate()?"true":"false" );
     
       <Password.h>.set("qwerty"); //set target password to qwerty
      //should print true, since qwerty == qwerty
      Serial.println(  <Password.h>.is("qwerty")?"true":"false" );
      //should print false, since qwerty != qwirty
      Serial.println( password.is("qwirty")?"true":"false" );
    }
     
    void loop(){/*nothing to loop*/}

