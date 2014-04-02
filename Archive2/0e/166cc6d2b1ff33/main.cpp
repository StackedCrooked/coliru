int direct(int n) { return (n % 2) ? 9 : 6; }

int to_false(int n) { return (n % 2) != false ? 9 : 6; }

int to_true(int n) { return (n % 2) == true ? 9 : 6; }

int to_bool_false(int n) { return bool(n % 2) != false ? 9 : 6; }

int to_bool_true(int n) { return bool(n % 2) == true ? 9 : 6; }

