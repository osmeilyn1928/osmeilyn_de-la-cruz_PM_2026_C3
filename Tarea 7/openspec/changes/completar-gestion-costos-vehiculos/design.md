# Diseño: Completar Gestión de Costos de Vehículos

## Base actual
- Archivo único: `Costos de vehiculos.c`.
- Modelo en memoria: variables globales para el vehículo y un arreglo `gastos[MAX_GASTOS]` con contador `n` y `siguiente_id`.
- Persistencia: archivo de texto `vehiculo_simple.txt` con registros `VEHICULO;...` y `GASTO;...`.
- Interfaz: menú de consola en `main` con opciones para vehículo, alta de gasto, listado, eliminación y reportes.

## Enfoque de cambios
- **Evolutivo, no reescritura:** conservar estructuras, funciones y formato de archivo existentes siempre que sea posible; extender/ajustar para cumplir los requisitos.
- **Compatibilidad de datos:** mantener compatibilidad con archivos ya guardados (incluyendo el comportamiento actual de carga) o definir una migración segura si se cambia el formato.

## Diseño funcional

### Vehículo
- Reutilizar `datos_vehiculo()` para registro/edición.
- Añadir comprobaciones de coherencia al editar (comparar odómetro inicial propuesto con kilómetros de gastos existentes) y mensajes claros.

### Gastos
- Mantener `struct Gasto` e ID incremental no reutilizable (`siguiente_id`).
- Centralizar/fortalecer validaciones de fecha, monto, kilometraje y litros (combustible vs. otros) reutilizando helpers existentes (`fecha_ok`, `leer_double`, `leer_long`, `limpiar_descripcion`).
- Mantener la lista ordenada por fecha en inserción y tras carga.

### Consulta y eliminación
- `listar()`: asegurar salida clara y completa; manejar caso vacío.
- `eliminar()`: validar ID de forma robusta, confirmar resultado y persistir.

### Reportes
- `reportes()`: conservar totales por categoría, total general y costo por km; evaluar agregar métricas simples (conteo, promedio) si aportan valor sin complicar la interfaz.

### Persistencia
- `guardar()/cargar()`: conservar formato actual; reforzar manejo de errores de E/S y tolerancia a líneas inválidas sin perder datos válidos cargados cuando sea seguro.

### Validación y UX
- Unificar lectura/validación de opciones numéricas para evitar aceptaciones parciales.
- Mensajes de error/éxito consistentes y retorno seguro al menú.

## Pruebas previstas (manuales y/o automatizadas si se acuerda)
- Casos válidos: registrar vehículo, registrar gastos de cada categoría, listar, eliminar, ver reportes, cerrar y reabrir verificando persistencia.
- Casos inválidos: fecha inexistente/formato malo, monto <= 0, km inválido o menor al permitido, litros inválidos en combustible, ID inexistente al eliminar, entradas no numéricas.
- Casos límite: sin vehículo, sin gastos, archivo inexistente, límite de gastos.
