#include <cstdlib>
#include <functional>
#include <utility>
#include <vector>

namespace hardware
{
    class Camera
    {
        public:
            using Guid          = unsigned int;
            using Temperature   = double;
            using Shutter       = double;
            using Gain          = double;
            using Framerate     = double;
            
            using Image = int;
            using Handler = std::function<void(Image const& image, Guid const& guid)>;
        
            Camera(Guid const& guid):
                guid_(guid)
            {}
            
            //! Getters
            //! \{
            Guid const& guid() const { return guid_; }
            Shutter const& shutter() const { return shutter_; }
            Gain const& gain() const { return gain_; }
            Framerate const& framerate() const { return framerate_; }
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
            
            Temperature temperature() const
            { return 0; }
            
            void trigger()
            {
                //Récupère une Image (API PTGR) et la passe au Board.
                handler_(Image(), guid());
            }
        
        private:
            Guid        guid_;
            Shutter     shutter_;
            Gain        gain_;
            Framerate   framerate_;
            Handler     handler_;
            
    };
    
    template<typename Camera>
    class Board:
    private std::pair<Camera, Camera>
    {
        public:
            using Guid          = typename Camera::Guid;
            using Temperature   = typename Camera::Temperature;
            using Shutter       = typename Camera::Shutter;
            using Gain          = typename Camera::Gain;
            using Framerate     = typename Camera::Framerate;
            
            using Image         = typename Camera::Image;
            using Handler = std::function<void(Image const& lhs, Image const& rhs)>;
            
            Board(Camera const& lhs, Camera const& rhs):
            std::pair<Camera, Camera>(lhs, rhs),
            visible_(0)
            {}
            
            std::vector<Temperature> temperature() const
            {
                std::vector<Temperature> output;
                output.push_back(this->first.temperature());
                output.push_back(this->second.temperature());
                // Add beam temperature sensors.
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
                // Changement du handler?
                this->first.visible();
                this->second.visible();
                visible_ = n;
            }
            
            void infrared()
            {
                // Changement du handler?
                this->first.infrared();
                this->second.infrared();
                visible_ = 0;
            }
            
            void trigger()
            {
                // Récupère les images des deux caméras.
                handler_(Image(), Image());
            }
                        
        private:
            size_t  visible_;
            Handler handler_;
            
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
            using Board<Camera>::trigger;
            using Board<Camera>::handler;
        
        private:
        
    };
} //namespace hardware

int main(int argc, char* argv[])
{
    using namespace hardware;
    using Image = typename Board<Camera>::Image;
    
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
    
    sensor.handler([](Image const& lhs, Image const& rhs){int i(0); ++i;});
    
    sensor.trigger();
    return 0;
}