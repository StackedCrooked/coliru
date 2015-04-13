using System.Web;
using System.Net;
using System.Text;
using System.IO;
using System;

public class Program {
    public static void Main(string[] args) {
        sendWebRequest();
    }

    private static void sendWebRequest() {
        HttpWebRequest req = (HttpWebRequest)WebRequest.Create("http://localhost:1313/RestBaby");
        req.Method = "POST";
        ServicePointManager.Expect100Continue = false;
        ServicePointManager.MaxServicePointIdleTime = 2000;
        req.KeepAlive = true;
        string postData = "This is a test that posts this string to a Web server.";
        byte[] byteArray = Encoding.UTF8.GetBytes(postData);
        // Set the ContentType property of the WebRequest.
        req.ContentType = "application/x-www-form-urlencoded";
        // Set the ContentLength property of the WebRequest.
        req.ContentLength = byteArray.Length;

        // Get the request stream.
        Stream dataStream = req.GetRequestStream();
        // Write the data to the request stream.
        dataStream.Write(byteArray, 0, byteArray.Length);
        // Close the Stream object.
        dataStream.Close();
        WebResponse rep = req.GetResponse();
    }
}
