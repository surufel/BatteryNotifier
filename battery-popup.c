#include<stdio.h>
#include<libnotify/notify.h>
/* Esse é o meu primeiro projeto do ano.
 * Estou fazendo isso não apenas por portfólio, eu tenho um problema
 * Estou usando Linux e percebi que algumas instalações limpas feitas em algumas distros como
 * a do Arch Linux não vem naturalmente com um notificador de bateria, a minha também não.
 * 
 * É um problema você estar usando seu notebook e do nada, ele descarregar.
 * Então, decidi produzir um notificador da porcentagem da bateria.
 *
 * Como esse programa também foi feito para fins de aprendizado, não usarei A.I. (Artificial Intelligence)
 * na produção desse programa. Apenas documentação das bibliotecas usadas.
 *
 * Claro, já existem distribuições que já possuem um programa com proposta igual, mas o meu intuito é
 * para aqueles que não tem, e querem o menor bloating possível e ainda com uma boa aparência
 * (que também é meu objetivo).
 * */

// Urgency Enum: 0 = Low Priority, 1 = Normal Priority, 2 = Critical Priority

int percent_read(){
    FILE *file_battery = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    // Battery capacity file address, read-only perm
    int percent = 0;
    if (file_battery){
        fscanf(file_battery, "%i", &percent);
        fclose(file_battery);
    }
    return percent;
}

int isCharging(){
    char status[20];
    FILE *charger_status("sys/class/power_supply/BAT0/status", "r");
    if (charger_stats){
        fscanf(f, "%s", status);
        fclose(charger_status);
        return (strcmp(status, "Discharging") == 0);
    }
    return 0;
}
    
int main(){

notify_init("BatteryAlert");
// Creating notifiers
NotifyNotification *charging = notify_notification_new(
        "CHARGING . . .",
        "The device is currently being charged.",
        "charging"
        );

NotifyNotification *lowAlert = notify_notification_new(
        "LOW BATTERY",
        "Your battery is low (15%), connect your device to a power supply!",
        "low-battery"
        );
NotifyNotification *urgencyAlert = notify_notification_new(
        "CRITICAL BATTERY PERCENTAGE",
        "Your battery is critically low (5%), hurry up and connect your device to a power supply!",
        "critically-low-battery"
        );

notify_notification_set_urgency(
        charging,
        0
        );

notify_notification_set_urgency(
        lowAlert,
        1
        );

notify_notification_set_urgency(
        urgencyAlert,
        2
        );

}





