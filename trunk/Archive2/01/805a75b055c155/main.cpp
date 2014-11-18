#include <cstdlib>
#include <functional>
#include <map>
#include <utility>

namespace hardware
{
  class Camera
  {
    public:
      typedef unsigned int Guid ;
      typedef double Temperature ;
      typedef double Shutter ;
      typedef double Gain ;
      typedef double Framerate ;

      typedef int Image ;
      typedef std::function<void(Image const& image, Guid const& guid)> Handler ;
      
      typedef int Archive;

      enum class State
      {
        Stop,
        Visible,
        Infrared,
        Error
      };

      enum class Error
      {
          NoError,
          Disconnected
        // Erreurs possibles
      };

      Camera(Guid const& guid):
        guid_(guid)
    {}

      //! Getters
      //! \{
      Guid const& guid() const { return guid_; }
      Shutter const& shutter() const { return shutter_; }
      Gain const& gain() const { return gain_; }
      Framerate const& framerate() const { return framerate_; }
      State const& state() const { return state_; }
      // Rajouter un std::bitset<Error::Size> pour lire plusieurs erreurs.
      // Rajouter un accés au bitset d'erreur si nécessaire.
      //! \}

      //! Setters
      //! \{
      Shutter const& shutter(Shutter const& s)
      {
        // Appel de l'API PTGR pour effectuer le changement.
        // Retour de la valeur réellement mise en place.
        return shutter();
      }
      
      Gain const& gain(Gain const& g)
      {
        // Appel de l'API PTGR pour effectuer le changement.
        // Retour de la valeur réellement mise en place.
        return gain();
      }
      
      Framerate const& framerate(Framerate const& f)
      {
        // Appel de l'API PTGR pour effectuer le changement.
        // Retour de la valeur réellement mise en place.
        return framerate();
      }
      
      void handler(Handler h)
      {
        handler_ = h;
      }
      //! \}

      //! Modes
      //! \Note Chaque type de camera possède ces réglages en dur.
      //! \{
      void visible() { /*Appels aux setters*/ }
      void infrared() { /*Appels aux setters*/ }
      //! \}

        //Retourne les temperatures interne et externe de la caméra.
      std::pair<Temperature, Temperature> temperature() const
      { return std::pair<Temperature, Temperature>(0, 0); }

      void trigger()
      {
        //Récupère une Image (API PTGR) et la passe au Board.
        handler_(Image(), guid());
      }
      
      void serialize(Archive & ar, const unsigned int version)
      {
          //TODO
      }

    private:
      Guid guid_;
      Shutter shutter_;
      Gain gain_;
      Framerate framerate_;
      Handler handler_;
      State state_;

  };

  template<typename Camera>
    class Board:
      private std::pair<Camera, Camera>
  {
    public:
      typedef typename Camera::Guid Guid ;
      typedef typename Camera::Temperature Temperature ;
      typedef typename Camera::Shutter Shutter ;
      typedef typename Camera::Gain Gain ;
      typedef typename Camera::Framerate Framerate ;

      typedef typename Camera::Image Image ;
      typedef std::function<void(Image const& lhs, Image const& rhs)> Handler ;

      typedef typename Camera::Archive Archive ;

      enum class State
      {
        Stop,
        Visible,
        Infrared,
        Error
      };

      enum class Error
      {
          NoError,
          DisonnectedRight,
          DisoconnectedLeft,
          Size
        // Erreurs possibles
      };
      
      // Rajouter un std::bitset<Error::Size> pour lire plusieurs erreurs.
      // Rajouter un accés au bitset d'erreur si nécessaire.

      Board(Camera const& lhs, Camera const& rhs):
        std::pair<Camera, Camera>(lhs, rhs),
        visible_(0)
    {}
    
    enum class TemperatureSensor
    {
        CameraInsideLeft,
        CameraOutsideLeft,
        CameraInsideRight,
        CameraOutsideRight,
        BeamLeft,
        BeamCenter,
        BeamRight,
        Ambiant
    };

      std::map<TemperatureSensor, Temperature> temperature() const
      {
        std::map<TemperatureSensor, Temperature> output;
        output[TemperatureSensor::CameraInsideLeft]     = this->first.temperature().first;
        output[TemperatureSensor::CameraOutsideLeft]    = this->first.temperature().second;
        output[TemperatureSensor::CameraInsideRight]    = this->second.temperature().first;
        output[TemperatureSensor::CameraOutsideRight]   = this->second.temperature().second;
        output[TemperatureSensor::BeamLeft]             = 0;
        output[TemperatureSensor::BeamCenter]           = 0;
        output[TemperatureSensor::BeamRight]            = 0;
        output[TemperatureSensor::Ambiant]              = 0;
        return output;
      }

      std::pair<Shutter, Shutter> shutter() const
      {
        return std::pair<Shutter, Shutter>
          (
           this->first.shutter(),
           this->second.shutter()
          );
      }

      std::pair<Shutter, Shutter> shutter(Shutter const& s)
      {
        return std::pair<Shutter, Shutter>
          (
           this->first.shutter(s),
           this->second.shutter(s)
          );
      }

      std::pair<Gain, Gain> gain() const
      {
        return std::pair<Gain, Gain>
          (
           this->first.gain(),
           this->second.gain()
          );
      }

      std::pair<Gain, Gain> gain(Gain const& g)
      {
        return std::pair<Gain, Gain>
          (
           this->first.gain(g),
           this->second.gain(g)
          );
      }

      std::pair<Framerate, Framerate> framerate() const
      {
        return std::pair<Framerate, Framerate>
          (
           this->first.framerate(),
           this->second.framerate()
          );
      }

      std::pair<Framerate, Framerate> framerate(Framerate const& f)
      {
        return std::pair<Framerate, Framerate>
          (
           this->first.framerate(f),
           this->second.framerate(f)
          );
      }

      void handler(Handler h)
      {
        handler_ = h;
      }

      //! Modes
      void visible(size_t n = 1)
      {
        this->first.visible();
        this->second.visible();
        visible_ = n;
      }

      void infrared()
      {
        this->first.infrared();
        this->second.infrared();
        visible_ = 0;
      }

      void trigger()
      {
        // Récupère les images des deux caméras.
        handler_(Image(), Image());
      }
      
      void start()
      {
          // Lance les acquisitions via le trigger des caméras.
          // A changer en startFlach et startCamera si nécessaire.
      }   
      
      void stop()
      {
          // Stop les acquisitions via le trigger des caméras.
          // A changer en stopFlach et stopCamera si nécessaire.
      }
      
      void serialize(Archive & ar, const unsigned int version)
      {
          this->first.serialize(ar, version);
          this->second.serialize(ar, version);
          //TODO
      }
      
      State const& state() const { return state_; }

    private:
      size_t visible_;
      Handler handler_;
      State state_;

  };

  template<typename Camera, template<typename> class Board>
    class Sensor:
      private Board<Camera>
  {
    public:
      Sensor(Board<Camera> const& board):
        Board<Camera>(board)
    {}

      using Board<Camera>::temperature;
      using Board<Camera>::shutter;
      using Board<Camera>::gain;
      using Board<Camera>::framerate;
      //! Pour les réglages des caméras
      //! \{
      using Board<Camera>::visible;
      using Board<Camera>::infrared;
      //! \}
      //! Pour les début/fin d'acquisition
      //! \{
      using Board<Camera>::start;
      using Board<Camera>::stop;
      //! \}
      // Rajouter accés au bitset d'erreur du board?
      
      typedef typename Board<Camera>::Archive Archive;
      
      void serialize(Archive & ar, const unsigned int version)
      {
          Board<Camera>::serialize(ar, version);
          //TODO
      }

    private:

  };
} //namespace hardware

int main(int argc, char* argv[])
{
  using namespace hardware;

  //! Construction des boards via une fonction de recherche du harware.
  //! \{
  Camera lhs(0), rhs(1);
  Board<Camera> board(lhs, rhs);
  //! \}

  Sensor<Camera, Board> sensor(board);
  auto temperature(sensor.temperature());
  auto shutter(sensor.shutter());
  auto gain(sensor.gain());
  auto framerate(sensor.framerate());
  return 0;
}
