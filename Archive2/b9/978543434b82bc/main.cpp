
    for quarter_value in range(0, 99, 25):
        set quarter_count = quarter_value / 25;
        set remain_after_quarters = 99-quarter_value;
        for dime_value in range(0, remain_after_quarters, 10):
            set dime_count = dime_value / 10;
            set remain_after_dimes = remain_after_quarters-dime_value;
            for nickel_value in range(0, remain_after_dimes, 5):
                set nickel_count = nickel_value / 5;
                set penny_count = remain_after_dimes-nickel_value;
                dioph_combinations.append(quarter_count, dime_count, nickel_count, penny_count);