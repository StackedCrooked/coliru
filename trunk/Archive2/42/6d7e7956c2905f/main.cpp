#include <boost/scoped_ptr.hpp>
#include <effidriver/observable_driver.hpp>

boost::scoped_ptr<effidriver::ObservableDriver> serial;

// ...

#include <effidriver/serial/termios/driver.hpp>

static effidriver::serial::TermiosParameter create_serial_parameters(const std::string & device_name) // /dev/ttyS0
{
  return effidriver::serial::TermiosParameter(
    device_name,
    effidriver::serial::TermiosParameter::DEFAULT_OPEN_FLAGS,
    effidriver::serial::TERMIOS_BAUD_RATE_115200,
    effidriver::serial::TERMIOS_NO_PARITY,
    false,
    false,
    effidriver::serial::TERMIOS_DATA_BITS_8,
    effidriver::serial::TERMIOS_STOP_BITS_1,
    effidriver::timeout::seconds(1),
    false);
}


static effidriver::ObservableDriver * create_observable_driver(const effidriver::serial::TermiosParameter & parameter)
{
  effidriver::Driver * driver(new effidriver::Driver(new effidriver::serial::TermiosDriver(parameter)));
  return new effidriver::ObservableDriver(driver);
}


void received_serial_data(
  const void * buffer, std::size_t buffer_size,
  const boost::posix_time::ptime &,
  const boost::system::error_code & ec)
{
  if (ec)
  {
    qWarning() << "read error: " << QString::fromStdString(ec.message());
    return;
  }
  // ...
}


serial.reset(create_observable_driver(create_serial_parameters("/dev/ttyS0")));
serial->add(this, boost::bind(&received_serial_data, this, _1, _2, _3, _4));




// ...

boost::system::error_code error;
serial->write(buffer, size, error);
if (error)
{
  qWarning() << "write error: " << QString::fromStdString(error.message());
  return;
}

// ...

