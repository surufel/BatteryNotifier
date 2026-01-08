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

int isDischarging(){
    char stats[11];
    FILE *charger_stats = fopen("/sys/class/power_supply/BAT0/status", "r");
    if (charger_stats){
        fscanf(charger_stats, "%s", stats);
        fclose(charger_stats);
        return (strcmp(stats, "Discharging") == 0);
    }
    return 0;
}
    
int main(){

notify_init("BatteryAlert");
// Creating notifiers

int last_alert_level = 0; // 0: Normal; 1: Charging; 2: Low; 3: Critical.
    while (1) {
        int percentage = percent_read();
        if (isDischarging()){
        if (percentage <= 10 && last_alert_level != 3) {
                NotifyNotification *urgencyAlert = notify_notification_new(
                "CRITICAL BATTERY PERCENTAGE",
                "Your battery is critically low (10%), hurry up and connect your device to a power supply!",
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
        } else if (percentage <= 20 && last_alert_level != 2) {
            NotifyNotification *lowAlert = notify_notification_new(
                "LOW BATTERY",
                "Your battery is low (15%), connect your device to a power supply!",
                "low-battery"
                );

                notify_notification_set_urgency(
                        lowAlert,
                        NOTIFY_URGENCY_CRITICAL
                        );

                notify_notification_show(
                        lowAlert,
                        NULL
                        );

                g_object_unref(G_OBJECT(lowAlert));
                last_alert_level = 2;
            }
        } else {
            if (last_alert_level != 1){
                NotifyNotification *charging = notify_notification_new(
                "CHARGING . . .",
                "The device is currently being charged.",
                "charging"
                );

                notify_notification_set_urgency(
                        charging,
                        NOTIFY_URGENCY_CRITICAL
                        );

                notify_notification_show(
                        charging,
                        NULL
                        );

                g_object_unref(G_OBJECT(charging));
                last_alert_level = 1;
            }

        if (percentage > 20){last_alert_level = 0;}
        }
                sleep(30); // Verifies every 30 seconds
            }
                notify_uninit();
                return 0;
    }





