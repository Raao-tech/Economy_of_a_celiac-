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
                que el PIB ideal es su maximo hsiorico, mientras que su Pib real es el que se haya dado el "año pasado" osea, el ultimo pib agrgado al historial

                En este caso su factor "b" se puede itnerpretar como el aumento de demanda ( b --> infinito) o disminucion de esta (b ---> -infinito).  Siendo una economía sobre demandante e incapaz de satisfacer dicha demanda (inflacionaria),  o una economia de muy baja demanda volviendola escasamente consumidora  y muy ahorrativa (defalcioanria)  Respectivamente.
        \## Choque(t) : 
                        es un valor aleatorio, suele ser calculado expresando subidas en el
                        precio de la energia. (podemos generarlo con time)
    Hay una posible modificacion a fututro que puede ser implementada con el fin de ser mucho mas exactos, pero el PIB ideal de una economia es calcualda como la d




    la Estrucutura de Economy esta pensada para hacer el hsitorial del Producto interno bruto


    Pesnando bien la estrcutra del proyecto, lo que haremos es lo siguiente,  en cada file text se tendra un compedio de los utimos 5 años con sus respectvos PIBs por cada economia presente, leugo,  calcularemos la media del crecimiento 



1. Velocidad de Convergencia (Speed of Convergence)
Es el término más común en el Modelo de Crecimiento de Solow. Se refiere a la rapidez con la que una economía cierra la brecha entre su estado actual y su estado estacionario (el promedio o nivel de equilibrio).

2. Coeficiente de Reversión a la Media (Mean Reversion Coefficient)
Este nombre se usa en el contexto de las Series Temporales (como el modelo de Vasicek en finanzas). Define la "fuerza" con la que el valor es arrastrado de vuelta hacia el promedio a largo plazo.

3. Factor de Amortiguamiento (Damping Factor)
Si ves la economía como un sistema físico (como un péndulo o un muelle), λ es lo que evita que el sistema oscile locamente. Es el rozamiento que frena los impulsos exagerados de los shocks (ϵ) para estabilizar el sistema.

4. Ajuste Parcial (Partial Adjustment)
En microeconomía, se llama así porque asume que los agentes económicos no pueden ajustar sus planes al 100% de forma instantánea, sino que solo ajustan una fracción (λ) de la diferencia deseada en cada periodo.

¿Cómo visualizar su impacto?
Si λ=1: El ajuste es instantáneo. No hay memoria. El PIB de Madrid volvería a su media en un solo año sin importar lo fuerte que fuera el shock.

Si λ=0: No hay ajuste. El sistema es un "Paseo Aleatorio" (Random Walk). El shock se queda ahí para siempre y la economía nunca intenta volver a su promedio.

Resumen para tu código:
En tu estructura Economy, podrías llamarla simplemente convergence_rate o mean_reversion_factor.

Para tu simulación:

Madrid: convergence_rate = 0.35 (Economía madura, vuelve al carril con relativa facilidad).

Caracas: convergence_rate = 0.05 (Economía con shocks persistentes, donde las crisis suelen durar mucho antes de empezar a recuperarse).

¿Cómo piensas inicializar esta variable en tu función create_economy? ¿Será un valor fijo o dejarás que el usuario lo configure?









    
