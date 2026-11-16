# Especificación: Gestión de Costos de Vehículos

## 1. Datos del vehículo
- El sistema debe permitir registrar y editar los datos de un vehículo: marca, modelo, placa, año y odómetro inicial.
- Debe validar que los campos obligatorios no estén vacíos, que el año sea razonable y que el odómetro inicial sea un valor numérico válido (no negativo).
- Al editar el vehículo, el sistema debe evitar dejar datos inconsistentes con los gastos ya registrados (p. ej. odómetro inicial incompatible con kilómetros registrados), informando al usuario.

## 2. Registro de gastos
- El sistema debe permitir registrar gastos con, al menos: identificador único, fecha, categoría, monto, kilometraje y descripción (y litros cuando aplique).
- Categorías soportadas: Combustible, Mantenimiento, Reparaciones, Seguro, Impuestos y Otros.
- Reglas de validación:
  - La fecha debe ser válida (formato esperado y fecha real de calendario).
  - El monto debe ser mayor que cero.
  - El kilometraje debe ser un valor numérico válido y coherente con el odómetro del vehículo.
  - Para Combustible, los litros deben ser mayores que cero; para otras categorías, los litros deben ser cero o un valor no negativo si se informan.
  - La descripción debe sanease/limitarse para no romper el formato de almacenamiento ni cortar caracteres multibyte.
- Cada gasto debe recibir un identificador único que no se reutilice tras eliminar otros gastos.

## 3. Consulta de gastos
- El sistema debe permitir consultar la lista de gastos registrados, mostrando de forma clara sus datos principales (ID, fecha, categoría, monto, kilometraje, litros si aplica, descripción).
- Si no hay gastos, debe informarlo claramente.

## 4. Eliminación de gastos
- El sistema debe permitir eliminar un gasto indicando su identificador.
- Si el identificador no existe, debe mostrar un mensaje claro sin modificar otros datos.
- Tras eliminar, los datos persistidos deben reflejar el cambio.

## 5. Totales y reportes
- El sistema debe calcular y mostrar el total de gastos.
- El sistema debe mostrar reportes útiles, al menos el desglose por categoría y el costo por kilómetro cuando pueda calcularse con los datos disponibles.
- Los reportes deben basarse en los gastos actualmente registrados.

## 6. Persistencia de datos
- El sistema debe guardar los datos (vehículo y gastos) en un archivo para conservarlos al cerrar el programa.
- Al iniciar, debe cargar los datos previamente guardados si el archivo existe y es válido; ante datos corruptos o incompatibles, debe manejar el error sin cerrarse inesperadamente.

## 7. Validación de entradas y experiencia de uso
- Todas las entradas del usuario (opciones de menú, números, fechas, textos) deben validarse.
- Ante entradas inválidas, el sistema debe mostrar mensajes claros y permitir continuar (p. ej. volver al menú) sin perder datos válidos ya guardados en memoria/archivo según corresponda.
- El comportamiento debe ser consistente en todo el programa.
