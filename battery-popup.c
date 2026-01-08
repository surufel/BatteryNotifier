#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<libnotify/notify.h>
#include<string.h>
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

 #define BATTERY_LOW_VALUE = 20
 #define BATTERY_CRITICAL_VALUE = 10

int last_alert_level = 0; // 0: Normal; 1: Charging; 2: Low; 3: Critical.

int percentage(){
    FILE *file_battery = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    // Battery capacity file address, read-only perm
    int percent = 0;
    if (file_battery){
        fscanf(file_battery, "%i", &percent);
        fclose(file_battery);
    }
    return percent;
}

int isDischarging(){
    char stats[12];
    FILE *charger_stats = fopen("/sys/class/power_supply/BAT0/status", "r");
    if (charger_stats){
        fscanf(charger_stats, "%s", stats);
        fclose(charger_stats);
        return (strcmp(stats, "Discharging") == 0);
    }
    return 0;
}

void critical_battery_percentage(){
                    NotifyNotification *urgencyAlert = notify_notification_new(
                "CRITICAL BATTERY PERCENTAGE",
                "Your battery is critically low, hurry up and connect your device to a power supply!",
                "critically-low-battery"
                );
                notify_notification_set_urgency(
                        urgencyAlert,
                        NOTIFY_URGENCY_CRITICAL
                        );
                
                notify_notification_show(
                        urgencyAlert,
                        NULL
                        );

                g_object_unref(G_OBJECT(urgencyAlert));
                last_alert_level = 3;
}

void low_battery_percentage(){
    NotifyNotification *lowAlert = notify_notification_new(
                "LOW BATTERY",
                "Your battery is low, connect your device to a power supply!",
                "low-battery"
                );

                notify_notification_set_urgency(
                        lowAlert,
                        NOTIFY_URGENCY_NORMAL
                        );

                notify_notification_show(
                        lowAlert,
                        NULL
                        );

                g_object_unref(G_OBJECT(lowAlert));
                last_alert_level = 2;
}

void charging_battery(){
NotifyNotification *charging = notify_notification_new(
                "CHARGING . . .",
                "The device is currently being charged.",
                "charging"
                );

                notify_notification_set_urgency(
                        charging,
                        NOTIFY_URGENCY_LOW
                        );

                notify_notification_show(
                        charging,
                        NULL
                        );

                g_object_unref(G_OBJECT(charging));
                last_alert_level = 1;
}
    
int main(){
notify_init("BatteryAlert");
// Creating notifiers
    while(1){
        int bat_percentage = percentage();
        if (isDischarging()){
            if (bat_percentage <= BATTERY_CRITICAL_VALUE){
                if(last_alert_level != 3){critical_battery_percentage();}}
                else if(bat_percentage <= BATTERY_CRITICAL_VALUE){
                    if(last_alert_level != 2){low_battery_percentage();}}
                else{last_alert_level = 0;}
            }
        else {
            if(last_alert_level != 1){charging_battery();}
        }
    sleep(2); // Verifies every 2 seconds
    }
notify_uninit();
return 0;

    }