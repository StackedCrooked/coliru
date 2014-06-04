Main() {
    Standard.Range.Delimited(0, 12) | Standard.Algorithm.ForEach(Standard.Range.StreamInserter(std.cout));
}