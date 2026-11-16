# Propuesta: Completar Gestión de Costos de Vehículos

## Objetivo
Completar y robustecer el programa en C `Costos de vehiculos.c` para gestionar de forma confiable los costos de un vehículo, manteniendo el funcionamiento actual y mejorando lo necesario para cumplir los requisitos definidos.

## Alcance
- Registrar y editar los datos del vehículo.
- Registrar gastos en categorías: Combustible, Mantenimiento, Reparaciones, Seguro, Impuestos y Otros.
- Consultar/listar gastos.
- Eliminar gastos por identificador.
- Calcular totales y mostrar reportes de costos.
- Guardar y cargar datos desde archivo para conservarlos al cerrar y reabrir el programa.
- Validar las entradas del usuario y manejar errores de forma clara.

## Fuera de alcance (por ahora)
- Interfaz gráfica.
- Múltiples vehículos simultáneos (salvo que se decida ampliar).
- Sincronización en red o base de datos externa.

## Estado actual (resumen)
El programa ya implementa un menú de consola, registro básico de vehículo y gastos, listado, eliminación por ID, reportes (totales por categoría/total/costo por km) y persistencia en `vehiculo_simple.txt` con validaciones parciales. Esta propuesta busca completar y unificar el comportamiento y las validaciones.

## Criterios de éxito
- Todas las operaciones solicitadas funcionan correctamente con datos válidos.
- Entradas inválidas se rechazan con mensajes claros sin corromper datos.
- Los datos persisten entre ejecuciones.
- Los cambios respetan y evolucionan el código existente (sin reescritura desde cero).
