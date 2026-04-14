# Economy_of_a_celiac

## Descripción

Este proyecto es un simulador económico diseñado para modelar el impacto financiero de la enfermedad celíaca en pacientes. El simulador calcula el poder adquisitivo de individuos afectados por la celiaquía, teniendo en cuenta los costos asociados con la alimentación sin gluten y otros factores económicos. Programado en C, forma parte de la asignatura de Informática y Sociedad en la UAM.

## Justificación

La enfermedad celíaca afecta a un porcentaje significativo de la población, obligando a los pacientes a seguir una dieta estricta sin gluten. Los productos sin gluten suelen ser más caros, lo que reduce significativamente el poder adquisitivo de las personas afectadas. Este simulador busca cuantificar estos efectos económicos para concienciar sobre la necesidad de políticas de apoyo y accesibilidad a alimentos sin gluten a precios asequibles.

## Limitaciones

El simulador tiene una limitación importante: no tiene en cuenta el costo de la vida más allá del dinero. Esto incluye aspectos como el impacto en la calidad de vida, el estrés emocional, las restricciones sociales y otros factores no monetarios que afectan a los pacientes celíacos. Esta omisión es la razón por la cual el monto que se aprecia como poder adquisitivo resulta tan poco realista y bajo en comparación con la realidad.

Además, para que sea un simulador fiel a la realidad, debería incluir la posibilidad de aumentar sus ingresos así como una variable de cashflow que le permita ahorrar.

## Instalación

Para compilar el proyecto, asegúrate de tener un compilador de C instalado (como GCC). Ejecuta el siguiente comando en la raíz del proyecto:

```bash
make
```

Esto generará el ejecutable principal.

## Uso

Después de compilar, ejecuta el simulador con:

```bash
make run
```

El programa leerá datos de pacientes y economías desde los archivos en las carpetas `Patients/` y `Economys/`, y generará resultados basados en los cálculos definidos en el código.

## Estructura del Proyecto

- `main.c`: Archivo principal que inicia el simulador.
- `Makefile`: Script de compilación.
- `Headers/`: Contiene los archivos de cabecera (.h) para las estructuras de datos y funciones.
- `Src/`: Código fuente de los motores (Engine_reader.c, Graphic_engine.c).
- `TADs/`: Implementaciones de los Tipos Abstractos de Datos (Economy.c, Engine.c, Patient.c).
- `Patients/`: Archivos de datos de pacientes por ciudad.
- `Economys/`: Archivos de datos económicos por ciudad.
- `README.md`: Este archivo.
- `LICENSE`: Licencia del proyecto.

## Contribución

Si deseas contribuir al proyecto, por favor abre un issue o envía un pull request en el repositorio. Asegúrate de seguir las mejores prácticas de código y documentar cualquier cambio.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Autor

Raao-tech











    
