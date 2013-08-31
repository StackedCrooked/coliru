static void outputXML(StreamResult stream, Document doc) throws TransformerConfigurationException, TransformerException {
    Transformer trans = TransformerFactory.newInstance().newTransformer();
    trans.setOutputProperty(OutputKeys.INDENT, "yes");
    trans.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
    DOMSource source = new DOMSource(doc);
    trans.transform(source, stream);
}