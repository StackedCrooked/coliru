using System;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using NUnit.Framework;
using Selenium;

namespace SeleniumTests
{
[TestFixture]
public class C Click
{
private ISelenium selenium;
private StringBuilder verificationErrors;

[SetUp]
public void SetupTest()
{
selenium = new DefaultSelenium("localhost", 4444, "*chrome", "http://www.logalys.org/");
selenium.Start();
verificationErrors = new StringBuilder();
}

[TearDown]
public void TeardownTest()
{
try
{
selenium.Stop();
}
catch (Exception)
{
// Ignore errors if unable to close the browser
}
Assert.AreEqual("", verificationErrors.ToString());
}

[Test]
public void TheC ClickTest()
{
    		selenium.Open("/pages/info/horaire/index.php");
			selenium.Click("css=a.navlinkon > font");
			selenium.WaitForPageToLoad("20000");
			selenium.Type("name=username", "gregory");
			selenium.Type("name=userpass", "gregory123");
			selenium.Click("css=input[type=\"Image\"]");
			selenium.WaitForPageToLoad("20000");
			selenium.Click("//td[26]/b/a/font");
			selenium.WaitForPageToLoad("20000");
			selenium.Click("css=a > img");
}
}
}