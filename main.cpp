#include <SFML/Graphics.hpp>
#include <fstream>

int X_kafelek = 64;
int Y_kafelek = 19;
const int Size_kafelka = 40;

const int Width = 1280;
const int Height = 800;

enum obiekt{ niebo = 0, ziemia = 1, woda = 2, wrog = 3, trawa = 4, skala = 5, nagroda = 6, drabina = 7};

struct Mapa_id
{
    sf::Sprite Spr;
    obiekt przedmiot;
};

struct sSiatka
{
    sf::RectangleShape pion;
    sf::RectangleShape poziom;
};

int main()
{

    ///tekstury kafelkow ;]

    sf::Texture textziemia;
    if (!textziemia.loadFromFile("graphics/ziemia.png"))
        return EXIT_FAILURE;

    sf::Texture texttrawa;
    if (!texttrawa.loadFromFile("graphics/trawa.png"))
        return EXIT_FAILURE;

    sf::Texture textskala;
    if (!textskala.loadFromFile("graphics/skala.png"))
        return EXIT_FAILURE;

    sf::Texture Twoda;
    if (!Twoda.loadFromFile("graphics/woda.png"))
        return EXIT_FAILURE;

    sf::Texture textniebo;
    if (!textniebo.loadFromFile("graphics/niebo.bmp"))
        return EXIT_FAILURE;

    sf::Texture Tenemy;
    if (!Tenemy.loadFromFile("graphics/enemy.png"))
        return EXIT_FAILURE;

    sf::Texture Taward;
    if (!Taward.loadFromFile("graphics/coin.png"))
        return EXIT_FAILURE;

    sf::Texture Tdrabina;
    if (!Tdrabina.loadFromFile("graphics/ladder.png"))
        return EXIT_FAILURE;

    ///okno aplikacji

    sf::RenderWindow app(sf::VideoMode(Width, Height), "Edytor map ;]");
    sf::View widok((sf::FloatRect(0, 0, Width, Height)));
    app.setView(widok);

    sf::Sprite PostawKlocka;
    PostawKlocka.setTexture(textziemia);

    obiekt Tekstura = niebo;

    ///mapa w tablicy

    std::ifstream fin("Level.map");

    if(fin.is_open()){
        fin >> Y_kafelek;
        fin >> X_kafelek;
    }

    Mapa_id Plansza[Y_kafelek][X_kafelek];

    ///interfejs?

    sf::RectangleShape granica( sf::Vector2f( Size_kafelka*X_kafelek, Size_kafelka*Y_kafelek ) );
    granica.setFillColor(sf::Color::Blue);
    granica.setOutlineColor(sf::Color::Red);
    granica.setOutlineThickness(10);

    sf::RectangleShape AktualnaKafelka( sf::Vector2f( Size_kafelka+10, Size_kafelka+10 ) );
    AktualnaKafelka.setOutlineColor(sf::Color::Green);
    AktualnaKafelka.setOutlineThickness(3);
    AktualnaKafelka.setTexture(PostawKlocka.getTexture());
    AktualnaKafelka.setPosition(10,10);

    ///siatka mapy

    sSiatka Siatka[Y_kafelek][X_kafelek];

    for (int i = 0; i < Y_kafelek; ++i){
            for (int j = 0 ; j < X_kafelek; ++j){
                Siatka[i][j].pion.setSize(sf::Vector2f( 1, Size_kafelka ) );
                Siatka[i][j].pion.setFillColor(sf::Color::Red);
                Siatka[i][j].pion.setPosition(j*Size_kafelka, i*Size_kafelka);;
                Siatka[i][j].poziom.setSize(sf::Vector2f( Size_kafelka, 1 ) );
                Siatka[i][j].poziom.setFillColor(sf::Color::Red);
                Siatka[i][j].poziom.setPosition(j*Size_kafelka, i*Size_kafelka);;
            }
        }

    ///odczyt mapy z pliku Level.txt jesli istnieje

    if (fin.is_open()){
        for (int i = 0; i < Y_kafelek; ++i){
            for (int j = 0; j < X_kafelek; ++j){

                int tmp;
                fin >> tmp;
                Plansza[i][j].przedmiot = static_cast<obiekt>(tmp);
                Plansza[i][j].Spr.setPosition(j*Size_kafelka,i*Size_kafelka);

                switch (Plansza[i][j].przedmiot)
                {
                case niebo:
                    Plansza[i][j].Spr.setTexture(textniebo);
                    break;
                case ziemia:
                    Plansza[i][j].Spr.setTexture(textziemia);
                    break;
                case woda:
                    Plansza[i][j].Spr.setTexture(Twoda);
                    break;
                case wrog:
                    Plansza[i][j].Spr.setTexture(Tenemy);
                    break;
                case trawa:
                    Plansza[i][j].Spr.setTexture(texttrawa);
                    break;
                case skala:
                    Plansza[i][j].Spr.setTexture(textskala);
                    break;
                case nagroda:
                    Plansza[i][j].Spr.setTexture(Taward);
                    break;
                case drabina:
                    Plansza[i][j].Spr.setTexture(Tdrabina);
                    break;
                default:
                    Plansza[i][j].Spr.setTexture(textniebo);
                    break;
                }
            }
        }
    }

    fin.close();

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        ///wybor kafelki

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ){
             PostawKlocka.setTexture(textniebo);
             Tekstura = niebo;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ){
             PostawKlocka.setTexture(textziemia);
             Tekstura = ziemia;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ){
             PostawKlocka.setTexture(Twoda);
             Tekstura = woda;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ){
             PostawKlocka.setTexture(Tenemy);
             Tekstura = wrog;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ){
             PostawKlocka.setTexture(texttrawa);
             Tekstura = trawa;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ){
             PostawKlocka.setTexture(textskala);
             Tekstura = skala;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ){
             PostawKlocka.setTexture(Taward);
             Tekstura = nagroda;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) ){
             PostawKlocka.setTexture(Tdrabina);
             Tekstura = drabina;
        }

        ///malowanie na ekranie

        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
             sf::Mouse::getPosition( app ).x + widok.getCenter().x - Width/2 > 0 &&
             sf::Mouse::getPosition( app ).x + widok.getCenter().x - Width/2 < Size_kafelka*X_kafelek &&
             sf::Mouse::getPosition( app ).y + widok.getCenter().y - Height/2 > 0 &&
             sf::Mouse::getPosition( app ).y + widok.getCenter().y - Height/2 < Size_kafelka*Y_kafelek ){

            int x = sf::Mouse::getPosition( app ).x + widok.getCenter().x - Width/2;
            int y = sf::Mouse::getPosition( app ).y + widok.getCenter().y - Height/2;

            x = x / Size_kafelka;
            y = y / Size_kafelka;

            Mapa_id tmp;
            tmp.Spr = PostawKlocka;
            tmp.Spr.setPosition(x*Size_kafelka, y*Size_kafelka);
            tmp.przedmiot = Tekstura;

            Plansza[y][x] = tmp;

        }

        ///widok kamery

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
            widok.move(1, 0);
            AktualnaKafelka.move(1,0);
            app.setView(widok);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
             widok.move(-1, 0);
             AktualnaKafelka.move(-1,0);
             app.setView(widok);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
             widok.move(0, -1);
             AktualnaKafelka.move(0,-1);
             app.setView(widok);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
             widok.move(0, 1);
             AktualnaKafelka.move(0,1);
             app.setView(widok);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) ){
            widok.reset(sf::FloatRect(0, 0, Width, Height));
            app.setView(widok);
            AktualnaKafelka.setPosition(10,10);
        }

        AktualnaKafelka.setTexture(PostawKlocka.getTexture());

        ///zapis do pliku

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ){

            std::ofstream fout("Level.map");

            fout << Y_kafelek << " " << X_kafelek << std::endl;

            for (int i = 0; i < Y_kafelek; ++i){
                for (int j = 0; j < X_kafelek; ++j){
                    fout << Plansza[i][j].przedmiot << " ";
                }
                fout << "\n";
            }

            fout.close();
        }

        app.clear();

        app.draw(granica);

        for (int i = 0; i < Y_kafelek; ++i){
            for (int j = 0; j < X_kafelek; ++j){
                app.draw(Plansza[i][j].Spr);
            }
        }

        for (int i = 0; i < Y_kafelek; ++i){
            for (int j = 0; j < X_kafelek; ++j){
                app.draw(Siatka[i][j].poziom);
                app.draw(Siatka[i][j].pion);
            }
        }

        app.draw(AktualnaKafelka);

        app.display();
    }

    return EXIT_SUCCESS;
}
