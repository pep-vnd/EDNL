#include <string>
#include "abb.h"

using namespace std;

struct Persona
{
    string nombre;
    string telefono;

    Persona(const string& n = "", const string& t = ""): nombre(n), telefono(t) {}

    bool operator<(const Persona& p) const
    {
        return nombre < p.nombre;
    }

    bool operator>(const Persona& p) const
    {
        return nombre > p.nombre;
    }

    bool operator==(const Persona& p) const
    {
        return nombre == p.nombre;
    }
};


class Agenda
{
private:

    Abb<Persona> personas;

    bool buscarPorTelefonoRec(const string& telefono, const Abb<Persona>& A, Persona& encontrada) const
    {
        if (A.vacio())
            return false;

        if (A.elemento().telefono == telefono)
        {
            encontrada = A.elemento();
            return true;
        }

        return buscarPorTelefonoRec(telefono, A.izqdo(), encontrada) || buscarPorTelefonoRec(telefono, A.drcho(), encontrada);
    }


public:

    void insertarPersona(const Persona& p)
    {
        personas.insertar(p);
    }


    void eliminarPersona(const Persona& p)
    {
        personas.eliminar(p);
    }


    string getTelefono(const string& nombre) const
    {
        Abb<Persona> resultado = personas.buscar(Persona(nombre, ""));

        if (resultado.vacio())
            return "";

        return resultado.elemento().telefono;
    }


    bool getPersonaPorTelefono(const string& telefono, Persona& encontrada) const
    {
        return buscarPorTelefonoRec(telefono,personas,encontrada);
    }
};