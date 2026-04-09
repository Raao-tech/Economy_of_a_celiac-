# Economy_of_a_celiac-
This is a project for the computer science and society subject at the UAM.    It simulates the economic and physical situation of a celiac based on macroeconomic variables and microeconomic decisions.  Programmed in C... is the initial idea



La idea que se va a usar para pdoer calcular la infalcion del siguiente mes, presente en la funcion
engine_next_month(Engine* engine), es la formula que sigue el BCE.

    \## La Curva de Phillips NeoKeynessiana (la Curva de Phillips)
        ** Inf (hoy) = a * Inf(mañana) + b * Brecha_productiva(t) +  Choque(t)
    Siendo:
        \## Brecha Pruductiva: 
                           **Es el porcentaje de variacion entre el PIB real y el PIB ideal 
                           **de la economía presente, siendo el punto idilico, 
                           **cuando (PIB_r - PIB_I = 0).
                Nosotros los calcumaos de forma sencilla pero no exacta,usamos los datos
                historicos del PIB de la economia elegida por elmnsuario, y liuego decimos
                que el PIB ideal es su maximo hsiorico, mientras que su Pib real es el que se vaya dando aleatoriamente en un array de PIBs hsotoricos bajasdos des un datasheet de uan fuente
        \## Choque(t) : 
                        es un valor aleatorio, suele ser calculado expresando subidas en el
                        precio de la energia. (podemos generarlo con time)
                        