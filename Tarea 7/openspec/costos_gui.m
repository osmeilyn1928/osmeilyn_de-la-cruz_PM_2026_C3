#import <Cocoa/Cocoa.h>
#include "costos_core.h"
#include <stdlib.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong) NSWindow *window;
@property (strong) NSTextField *marcaField;
@property (strong) NSTextField *modeloField;
@property (strong) NSTextField *placaField;
@property (strong) NSTextField *anioField;
@property (strong) NSTextField *odometroField;

@property (strong) NSTextField *fechaField;
@property (strong) NSPopUpButton *categoriaPopup;
@property (strong) NSTextField *montoField;
@property (strong) NSTextField *kmField;
@property (strong) NSTextField *litrosField;
@property (strong) NSTextField *descField;

@property (strong) NSTextField *idEliminarField;
@property (strong) NSTextView *resultadoView;
@end

static NSString *ns(const char *s) { return s ? [NSString stringWithUTF8String:s] : @""; }

@implementation AppDelegate

- (void)appendTexto:(NSString *)texto {
    NSString *actual = self.resultadoView.string ?: @"";
    NSString *nuevo = [actual stringByAppendingFormat:@"%@\n", texto];
    [self.resultadoView setString:nuevo];
    [self.resultadoView scrollRangeToVisible:NSMakeRange(nuevo.length, 0)];
}

- (NSTextField *)label:(NSString *)text frame:(NSRect)frame {
    NSTextField *l = [[NSTextField alloc] initWithFrame:frame];
    [l setStringValue:text];
    [l setBezeled:NO];
    [l setDrawsBackground:NO];
    [l setEditable:NO];
    [l setSelectable:NO];
    return l;
}

- (NSTextField *)input:(NSRect)frame placeholder:(NSString *)ph {
    NSTextField *f = [[NSTextField alloc] initWithFrame:frame];
    [f setPlaceholderString:ph ?: @""];
    return f;
}

- (void)registrarVehiculo:(id)sender {
    const char *marca = [[self.marcaField stringValue] UTF8String];
    const char *modelo = [[self.modeloField stringValue] UTF8String];
    const char *placa = [[self.placaField stringValue] UTF8String];
    int anio_v = [[self.anioField stringValue] intValue];
    long odo = [[[self.odometroField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] length] ? atol([[self.odometroField stringValue] UTF8String]) : -1;
    char msg[256];

    /* Validación básica de entrada numérica antes de pasar al núcleo */
    NSString *anioStr = [[self.anioField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *odoStr = [[self.odometroField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    if (anioStr.length == 0 || odoStr.length == 0) {
        [self appendTexto:@"Error: año y odómetro son obligatorios."];
        return;
    }
    char *end1=NULL, *end2=NULL;
    strtol([anioStr UTF8String], &end1, 10);
    strtol([odoStr UTF8String], &end2, 10);
    if (!end1 || *end1 != '\0' || !end2 || *end2 != '\0') {
        [self appendTexto:@"Error: año y odómetro deben ser números enteros válidos."];
        return;
    }
    anio_v = (int)strtol([anioStr UTF8String], NULL, 10);
    odo = strtol([odoStr UTF8String], NULL, 10);

    if (costos_registrar_vehiculo(marca, modelo, placa, anio_v, odo, msg, sizeof msg)) {
        [self appendTexto:ns(msg)];
    } else {
        [self appendTexto:ns(msg)];
    }
}

- (void)agregarGasto:(id)sender {
    const char *fecha = [[self.fechaField stringValue] UTF8String];
    NSInteger catIdx = [self.categoriaPopup indexOfSelectedItem];
    NSString *montoStr = [[self.montoField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *kmStr = [[self.kmField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *litrosStr = [[self.litrosField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    const char *desc = [[self.descField stringValue] UTF8String];
    char *e1=NULL,*e2=NULL,*e3=NULL;
    double monto = strtod([montoStr UTF8String], &e1);
    long km = strtol([kmStr UTF8String], &e2, 10);
    double litros = strtod([litrosStr UTF8String], &e3);
    unsigned long id_out = 0;
    char msg[256];

    if (montoStr.length==0 || !e1 || *e1!='\0') { [self appendTexto:@"Error: monto inválido."]; return; }
    if (kmStr.length==0 || !e2 || *e2!='\0') { [self appendTexto:@"Error: kilometraje inválido."]; return; }
    if (litrosStr.length==0 || !e3 || *e3!='\0') { [self appendTexto:@"Error: litros inválidos."]; return; }

    if (costos_agregar_gasto(fecha, (int)catIdx, monto, km, litros, desc, &id_out, msg, sizeof msg)) {
        [self appendTexto:ns(msg)];
    } else {
        [self appendTexto:ns(msg)];
    }
}

- (void)listarGastos:(id)sender {
    char buffer[8192];
    costos_obtener_lista(buffer, sizeof buffer);
    [self appendTexto:@"--- Lista de gastos ---"];
    [self appendTexto:ns(buffer)];
}

- (void)eliminarGasto:(id)sender {
    NSString *idStr = [[self.idEliminarField stringValue] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    if (idStr.length == 0) { [self appendTexto:@"Error: debe indicar un ID."]; return; }
    char *end=NULL;
    unsigned long idv = strtoul([idStr UTF8String], &end, 10);
    if (!end || *end != '\0') { [self appendTexto:@"Error: ID inválido."]; return; }
    char msg[256];
    if (costos_eliminar_gasto(idv, msg, sizeof msg)) [self appendTexto:ns(msg)];
    else [self appendTexto:ns(msg)];
}

- (void)mostrarReporte:(id)sender {
    char buffer[4096];
    costos_obtener_reporte(buffer, sizeof buffer);
    [self appendTexto:@"--- Reporte ---"];
    [self appendTexto:ns(buffer)];
}

- (void)guardarSalirInfo:(id)sender {
    char msg[256];
    if (costos_guardar(msg, sizeof msg)) [self appendTexto:@"Datos guardados correctamente."];
    else [self appendTexto:ns(msg)];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    costos_cargar();

    NSRect frame = NSMakeRect(0, 0, 980, 720);
    self.window = [[NSWindow alloc] initWithContentRect:frame
                                              styleMask:(NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskResizable|NSWindowStyleMaskMiniaturizable)
                                                backing:NSBackingStoreBuffered defer:NO];
    [self.window setTitle:@"Gestión de Costos de Vehículos"];
    [self.window center];

    NSView *cv = [self.window contentView];
    CGFloat yTop = 680;

    [cv addSubview:[self label:@"Vehículo" frame:NSMakeRect(20, yTop, 200, 20)]];
    [cv addSubview:[self label:@"Marca:" frame:NSMakeRect(20, yTop-30, 60, 20)]];
    self.marcaField = [self input:NSMakeRect(80, yTop-32, 140, 24) placeholder:@""];
    [cv addSubview:self.marcaField];
    [cv addSubview:[self label:@"Modelo:" frame:NSMakeRect(230, yTop-30, 60, 20)]];
    self.modeloField = [self input:NSMakeRect(290, yTop-32, 140, 24) placeholder:@""];
    [cv addSubview:self.modeloField];
    [cv addSubview:[self label:@"Placa:" frame:NSMakeRect(440, yTop-30, 50, 20)]];
    self.placaField = [self input:NSMakeRect(490, yTop-32, 120, 24) placeholder:@""];
    [cv addSubview:self.placaField];
    [cv addSubview:[self label:@"Año:" frame:NSMakeRect(620, yTop-30, 40, 20)]];
    self.anioField = [self input:NSMakeRect(660, yTop-32, 70, 24) placeholder:@"2020"];
    [cv addSubview:self.anioField];
    [cv addSubview:[self label:@"Odómetro:" frame:NSMakeRect(740, yTop-30, 70, 20)]];
    self.odometroField = [self input:NSMakeRect(810, yTop-32, 90, 24) placeholder:@"0"];
    [cv addSubview:self.odometroField];
    NSButton *btnVeh = [[NSButton alloc] initWithFrame:NSMakeRect(20, yTop-65, 220, 28)];
    [btnVeh setTitle:@"Registrar/Actualizar vehículo"];
    [btnVeh setTarget:self];
    [btnVeh setAction:@selector(registrarVehiculo:)];
    [btnVeh setBezelStyle:NSBezelStyleRounded];
    [cv addSubview:btnVeh];

    CGFloat yG = yTop - 105;
    [cv addSubview:[self label:@"Registrar gasto" frame:NSMakeRect(20, yG, 200, 20)]];
    [cv addSubview:[self label:@"Fecha (AAAA-MM-DD):" frame:NSMakeRect(20, yG-30, 140, 20)]];
    self.fechaField = [self input:NSMakeRect(160, yG-32, 110, 24) placeholder:@"2026-01-01"];
    [cv addSubview:self.fechaField];
    [cv addSubview:[self label:@"Categoría:" frame:NSMakeRect(280, yG-30, 70, 20)]];
    self.categoriaPopup = [[NSPopUpButton alloc] initWithFrame:NSMakeRect(350, yG-34, 170, 26) pullsDown:NO];
    for (int i=0;i<6;i++) [self.categoriaPopup addItemWithTitle:ns(CATEGORIAS[i])];
    [cv addSubview:self.categoriaPopup];
    [cv addSubview:[self label:@"Monto:" frame:NSMakeRect(530, yG-30, 50, 20)]];
    self.montoField = [self input:NSMakeRect(580, yG-32, 90, 24) placeholder:@"0.00"];
    [cv addSubview:self.montoField];
    [cv addSubview:[self label:@"Km:" frame:NSMakeRect(680, yG-30, 30, 20)]];
    self.kmField = [self input:NSMakeRect(710, yG-32, 90, 24) placeholder:@"0"];
    [cv addSubview:self.kmField];
    [cv addSubview:[self label:@"Litros:" frame:NSMakeRect(810, yG-30, 45, 20)]];
    self.litrosField = [self input:NSMakeRect(855, yG-32, 80, 24) placeholder:@"0"];
    [cv addSubview:self.litrosField];
    [cv addSubview:[self label:@"Descripción:" frame:NSMakeRect(20, yG-60, 80, 20)]];
    self.descField = [self input:NSMakeRect(100, yG-62, 600, 24) placeholder:@"Descripción"];
    [cv addSubview:self.descField];
    NSButton *btnG = [[NSButton alloc] initWithFrame:NSMakeRect(710, yG-64, 150, 28)];
    [btnG setTitle:@"Agregar gasto"];
    [btnG setTarget:self];
    [btnG setAction:@selector(agregarGasto:)];
    [btnG setBezelStyle:NSBezelStyleRounded];
    [cv addSubview:btnG];

    CGFloat yA = yG - 105;
    [cv addSubview:[self label:@"Acciones" frame:NSMakeRect(20, yA, 200, 20)]];
    NSButton *btnList = [[NSButton alloc] initWithFrame:NSMakeRect(20, yA-32, 140, 28)];
    [btnList setTitle:@"Listar gastos"]; [btnList setTarget:self]; [btnList setAction:@selector(listarGastos:)]; [btnList setBezelStyle:NSBezelStyleRounded]; [cv addSubview:btnList];
    NSButton *btnRep = [[NSButton alloc] initWithFrame:NSMakeRect(170, yA-32, 140, 28)];
    [btnRep setTitle:@"Ver reporte"]; [btnRep setTarget:self]; [btnRep setAction:@selector(mostrarReporte:)]; [btnRep setBezelStyle:NSBezelStyleRounded]; [cv addSubview:btnRep];
    [cv addSubview:[self label:@"ID a eliminar:" frame:NSMakeRect(330, yA-28, 90, 20)]];
    self.idEliminarField = [self input:NSMakeRect(420, yA-32, 80, 24) placeholder:@"ID"];
    [cv addSubview:self.idEliminarField];
    NSButton *btnDel = [[NSButton alloc] initWithFrame:NSMakeRect(510, yA-32, 140, 28)];
    [btnDel setTitle:@"Eliminar gasto"]; [btnDel setTarget:self]; [btnDel setAction:@selector(eliminarGasto:)]; [btnDel setBezelStyle:NSBezelStyleRounded]; [cv addSubview:btnDel];
    NSButton *btnSave = [[NSButton alloc] initWithFrame:NSMakeRect(660, yA-32, 140, 28)];
    [btnSave setTitle:@"Guardar datos"]; [btnSave setTarget:self]; [btnSave setAction:@selector(guardarSalirInfo:)]; [btnSave setBezelStyle:NSBezelStyleRounded]; [cv addSubview:btnSave];

    [cv addSubview:[self label:@"Resultados" frame:NSMakeRect(20, yA-70, 200, 20)]];
    NSScrollView *scroll = [[NSScrollView alloc] initWithFrame:NSMakeRect(20, 20, 940, yA-80)];
    [scroll setHasVerticalScroller:YES];
    [scroll setHasHorizontalScroller:YES];
    [scroll setBorderType:NSBezelBorder];
    self.resultadoView = [[NSTextView alloc] initWithFrame:NSMakeRect(0, 0, 920, yA-80)];
    [self.resultadoView setEditable:NO];
    [self.resultadoView setFont:[NSFont fontWithName:@"Menlo" size:12]];
    [self.resultadoView setString:@"Listo. Puede registrar un vehículo, agregar gastos, listar, eliminar y ver reportes.\n"];
    [scroll setDocumentView:self.resultadoView];
    [cv addSubview:scroll];

    /* Precargar campos de vehículo si existe */
    if (hay_vehiculo) {
        [self.marcaField setStringValue:ns(marca)];
        [self.modeloField setStringValue:ns(modelo)];
        [self.placaField setStringValue:ns(placa)];
        [self.anioField setStringValue:[NSString stringWithFormat:@"%d", anio]];
        [self.odometroField setStringValue:[NSString stringWithFormat:@"%ld", odometro]];
        [self appendTexto:@"Datos del vehículo cargados desde archivo."];
    }

    [self.window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender { return YES; }
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        [app setActivationPolicy:NSApplicationActivationPolicyRegular];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];
        [app run];
    }
    return 0;
}
