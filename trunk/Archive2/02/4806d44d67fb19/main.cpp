template <class T, unsigned int inputs = 1, unsigned int outputs = 1>
class Filter {
public:
    virtual Data<T, outputs> getOutput(const Data<T, inputs> &sample) = 0;
    virtual void getOutput(const Data<T, inputs> &sample, Data<T, outputs> *out) = 0;
    virtual void reset() = 0;
    virtual void set(const std::map<std::string, boost::any> &options) = 0; 
};

template <class T, int addends = 2>
class Sum : public Filter<T, addends, 1> {
public:
    Sum();
    virtual ~Sum() {};
    virtual Data<T, 1> getOutput(const Data<T, addends> &sample);
    virtual void getOutput(const Data<T, addends> &sample, Data<T, 1> *out);
    virtual void reset();
    virtual void set(const std::map<std::string, boost::any> &options);

private:

};

int
main()
{
    Sum<int, 2> sum;
}