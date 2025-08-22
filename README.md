# Autocutre

##### Autocutre es un programa para representar figuras geometricas en un plano 2d.<br>Puede hacer tareas basicas de manipulación como rotar, crear , eliminar .

# Requisitos

* **Cmake**: Para compilar el proyecto.
* **SDL2**: Para manipular pantalla.
* **SDL2_image**: Cargar las imagenes de los botones.
* **SDL2_ttf**: Para mostrar texto en la pantalla.

# Compilar y ejecutar

1. Clonar el repositorio:
```git clone https://github.com/mtcraft22/Autocutre.git```

2. Moverse al directorio del repositorio:
```cd ./Autocutre```

3. Crear carpeta build:
```mkdir build```

```cd ./build```

4. Compilar:
```cmake ../```

```cmake --build ./```

5. Copiar el directorio de los assets:

    Desde la carpeta build:

        1. ```cd ./src```

        2. ```cp -d -r ../../res ./```

6. Ejecutar:
    En el directorio build/src
   
    ``` ./Autocutre```
