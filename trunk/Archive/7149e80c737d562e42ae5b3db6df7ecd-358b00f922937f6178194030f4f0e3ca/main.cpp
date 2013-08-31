305 bool VtController::isSupportedVideoFile(const std::string & inFile) const
306 {
307     static std::vector<std::string> fExtensions = []() -> std::vector<std::string> {
            std::vector<std::string> fExtensions;
310         fExtensions.push_back("avi");
311         fExtensions.push_back("3gp");
312         fExtensions.push_back("mpg");
313         fExtensions.push_back("mpeg");
314         fExtensions.push_back("flv");
315         fExtensions.push_back("mp4");
316         fExtensions.push_back("m4v");
317         fExtensions.push_back("mov");
318         fExtensions.push_back("rm");
319         fExtensions.push_back("wmv");
320         fExtensions.push_back("mp4");
            return fExtensions;
321     }();
322     std::string ext = Netlog::StrToLower(Poco::Path(inFile).getExtension());
323     return find(fExtensions.begin(), fExtensions.end(), ext) != fExtensions.end();
324 }
