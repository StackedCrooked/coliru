cat <<HERE > input.txt && g++-4.8 -std=c++11 -Os -Wall -pedantic main.cpp && ./a.out
begin
    declare x : int;
    declare y : string;

    let x = 42;
    let y = "Life the universe and everything";

    for(ch : y)
    begin
        if (call is_alpha(ch))
        begin
            declare z : string;
            let z = call to_upper(ch);
            call print(z);
        end; 
        else call print("?");
    end;
end;

HERE