#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<libnotify/notify.h>
#include<string.h>

 #define BATTERY_LOW_VALUE = 20
 #define BATTERY_CRITICAL_VALUE = 10
 #define BAT_CAPACITY "/sys/class/power_supply/BAT0/capacity"
 #define BAT_STATUS "/sys/class/power_supply/BAT0/status"

int last_alert_level = 0; // 0: Normal; 1: Charging; 2: Low; 3: Critical.

int percentage(){
    FILE *file_battery = fopen(BAT_CAPACITY, "r");
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
    FILE *charger_stats = fopen(BAT_STATUS, "r");
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
