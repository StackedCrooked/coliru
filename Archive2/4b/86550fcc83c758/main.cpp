string Chiper(string phrase,int K)
{
    K = K % 26;
    for(size_t i=0;i<phrase.length();i++)
    {
        if(phrase[i]>='A'&& phrase[i]<='Z')
        {
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'Z')
            {
                phrase[i]=phrase[i]-26;
            }
            if(phrase[i]<'A')
            {
                phrase[i]=phrase[i]+26;
            }
        }//Maj case

        if(phrase[i]>='a'&& phrase[i]<='z')
        {
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'z')
            {
                phrase[i]=phrase[i]-26;
            }
            if(phrase[i]<'a')
            {
                phrase[i]=phrase[i]+26;
            }
        }//Min case

        if(phrase[i]>='0' && phrase[i]<='9')
        {
            K=K%10;
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'9')
            {
                phrase[i]=phrase[i]-10;
            }
            if(phrase[i]<'0')
            {
                phrase[i]=phrase[i]+10;
            }//number case
            //no change for weird carac not deleted
        }
    }
    cout<<phrase<<endl;
    return phrase;
}