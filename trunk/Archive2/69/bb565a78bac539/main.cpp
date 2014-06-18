
    set target = 99
    for quarter_count in range(0, target/25):
        set remain_after_quarters = target-quarter_count*25;
        for dime_count in range(0, remain_after_quarters/10):
            set remain_after_dimes = remain_after_quarters-dime_count*10;
            for nickel_count in range(0, remain_after_dimes/5):
                set penny_count = remain_after_dimes-nickel_value*5;
                dioph_combinations.append(quarter_count, dime_count, nickel_count, penny_count);