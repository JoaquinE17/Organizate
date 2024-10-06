###########################
GESTOR DE TAREAS
###########################

El proyecto brinda la posibilidad de crea una lista de tareas pendientes durante el dia. Este programa basico presenta lo siguiente:
  1) Un menu principal con opciones basicas:
        -Insertar tareas
        -Mostrar tareas
        -*Modificar tareas
        -Exportar lista de tareas
        -Finalizar programa
  2) Un submenu destinado a la *modificacion:
        -Marcar tareas realizadas:
            .Presenta un selector que se desplaza arriba y abajo para marcar la tarea realizada.
        -Vaciar la lista de tareas
        -*Hacer cambios en la lista
        -Volver (menu principal)
  3) El submenu '*Hacer cambios...' presenta las sig. opciones:
        -Revertir tarea marcada
        -Corregir una tarea de la lista
        -Volver al menu anterior

FEEDBACK:
  . Agregar la opcion de 'CANCELAR' en los siguientes modulos:
        -modtarea_tr
        -revertir_check
        -Y en todas donde sea conveniente (por ejelmplo: al momento de agragar tareas)
  . Hacer que en 'exportar_tarea', el usuario introduzca nombre del archivo