var attr1 = new ItemTemplateAttribute();
var attr2 = new ItemTemplateAttribute();

var assign_bounds1 = new List<Action<int>>() {
    x => attr1.lower_min = x, x => attr1.lower_max = x, x => attr1.upper_min = x, x => attr1.upper_max = x
};

var assign_bounds2 = new List<Action<int>>() {
    x => attr2.lower_min = x, x => attr2.lower_max = x, x => attr2.upper_min = x, x => attr2.upper_max = x
};

for(int i=0; i < 4; ++i)
{
    Func<int, int> selector = id => Convert.ToInt32(
        new MySqlCommand(String.Format(format, attr_name, bound_names[i], id), m_form.Connection)
        .ExecuteScalar()
    );
    var s1 = ids1.Select(selector).Sum();
    var s2 = ids2.Select(selector).Sum();
    assign_bounds1[i](ids1.Select(selector).Sum());
    assign_bounds2[i](ids2.Select(selector).Sum());
}
