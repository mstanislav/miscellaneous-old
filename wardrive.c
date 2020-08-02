/*
Required: GTK+ 2 libraries;development; and whatver else it takes along with pkg-config
Compile with: gcc -Wall -g wardrive.c -o wardrive `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
Created by: KryptoBSD (kryptobsd@uncompiled.com) www.uncompiled.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

/*Establish widgits to be used*/
    GtkWidget *window1;
    GtkWidget *ethereal;
    GtkWidget *airsnort;
    GtkWidget *ettercap;
    GtkWidget *xfsamba;
    GtkWidget *kismet;
    GtkWidget *nmapfe;
    GtkWidget *driftnet;
    GtkWidget *urlsnarf;
    GtkWidget *separator1;
    GtkWidget *killsniffers;
    GtkWidget *restartpcmcia;
    GtkWidget *killdhcp_bttn;
    GtkWidget *separator2;
    GtkWidget *ssidconfig;
    GtkWidget *wlandevice;
    GtkWidget *wlanconfig_bttn;
    GtkWidget *separator3;
    GtkWidget *ifconfigip;
    GtkWidget *ifconfigip_bttn;
    GtkWidget *dhcp_bttn;
    GtkWidget *separator4;
    GtkWidget *scrollbar;
    GtkObject *adj1;
    GtkWidget *sonylabel;
    GtkWidget *separator5;
    GtkWidget *screenshot_bttn;
    GtkWidget *log_bttn;
    GtkWidget *table;

static void call_ethereal( GtkWidget *widget,
         	          gpointer   data )
{
    system ("ethereal &");
}

static void call_airsnort( GtkWidget *widget,
                          gpointer   data )
{
    system ("airsnort &");
}

static void call_ettercap( GtkWidget *widget,
                          gpointer   data )
{
    const char *textwlan;
    char final_string[65];
    textwlan = gtk_entry_get_text(GTK_ENTRY(wlandevice));
    sprintf(final_string, "/usr/local/sbin/ettercap -G -d -i %s 2&>/dev/null &", textwlan);
    system(final_string);
}

static void call_xfsamba( GtkWidget *widget,
                          gpointer   data )
{
    system ("xfsamba &");
}

static void call_kismet( GtkWidget *widget,
                          gpointer   data )
{
    system ("gnome-terminal --geometry 150x50+10+20 -x kismet 2&>/dev/null &");
}

static void call_nmapfe( GtkWidget *widget,
                          gpointer   data )
{
    system ("nmapfe &");
}

static void call_driftnet( GtkWidget *widget,
                           gpointer   data )
{
    const char *textwlan;
    char final_string[30];
    textwlan = gtk_entry_get_text(GTK_ENTRY(wlandevice));
    sprintf(final_string, "driftnet -i %s &", textwlan);
    system(final_string);
}

static void call_urlsnarf( GtkWidget *widget,
                          gpointer   data )
{
    const char *textwlan;
    char final_string[65];
    textwlan = gtk_entry_get_text(GTK_ENTRY(wlandevice));
    sprintf(final_string, "gnome-terminal --geometry 150x50+10+20 -x urlsnarf -i %s 2&>/dev/null &", textwlan);
    system(final_string);
}

static void call_killsniffers( GtkWidget *widget,
                                gpointer   data )
{
    system ("killall airsnort 2&>/dev/null");
    system ("killall ethereal 2&>/dev/null");
    system ("killall kismet 2&>/dev/null");
}

static void call_restartpcmcia( GtkWidget *widget,
                                gpointer   data )
{
    system ("/etc/init.d/pcmcia restart 2&>/dev/null");
}

static void call_ssidconfig( GtkWidget *widget,
                             gpointer   data  )
{
const char *textssid;
const char *textwlan;
char final_string[65];
textssid = gtk_entry_get_text(GTK_ENTRY(ssidconfig));
textwlan = gtk_entry_get_text(GTK_ENTRY(wlandevice));
system("echo '#! /bin/sh' > /etc/wlan/wlan.conf");
sprintf(final_string, "echo 'WLAN_DEVICES=\"%s\"' >> /etc/wlan/wlan.conf", textwlan);
system(final_string);
system("echo 'ChannelList=\"01:02:03:04:05:06:07:08:09:0a:0b:00:00:00\"' >> /etc/wlan/wlan.conf");
system("echo 'ChannelMinTime=200' >> /etc/wlan/wlan.conf");
system("echo 'ChannelMaxTime=250' >> /etc/wlan/wlan.conf");
system("echo 'WLAN_SCAN=n' >> /etc/wlan/wlan.conf");
sprintf(final_string,"echo 'SSID_%s=\"%s\"' >> /etc/wlan/wlan.conf",textwlan,textssid);
system(final_string);
sprintf(final_string,"echo 'ENABLE_%s=y' >> /etc/wlan/wlan.conf",textwlan);
system(final_string);
system ("/etc/init.d/pcmcia restart 2&>/dev/null");
}

static void call_ifconfigip( GtkWidget *widget,
                             gpointer	data  )
{
  const char *setiptext;
  char final_string[30];
  setiptext = gtk_entry_get_text(GTK_ENTRY (ifconfigip));
  sprintf(final_string,"ifconfig wlan0 %s", setiptext);
  system(final_string);
}

static void call_dhcp( GtkWidget *widget,
                       gpointer   data  )
{
  const char *textwlan;
  char final_string[30];
  textwlan = gtk_entry_get_text(GTK_ENTRY(wlandevice));
  sprintf(final_string,"dhclient %s &", textwlan);
  system(final_string);
}

static void call_killdhcp( GtkWidget *widget,
                           gpointer   data  )
{
  system("killall dhclient 2&>1");
}

static void call_scroll( GtkAdjustment *adj, 
                         gpointer      data)
{
  char final_string[30];
  sprintf(final_string, "spicctrl -b %f", adj->value);
  system(final_string);
}

static void call_screenshot( GtkWidget *widget,
                             gpointer   data  )
{  
  system("gnome-panel-screenshot 2&>/dev/null &");
}

static void call_log( GtkWidget *widget,
                             gpointer   data  )
{
  system("xterm -geometry 150x50+10+20 -e nano /root/wifilocations &");
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}


int main(int argc, char *argv[])
{

    gtk_init (&argc, &argv);

/*Create window1 - Create widgit table - Establish buttons*/
    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (window1), 0);
    table = gtk_table_new (1, 1, TRUE);
    ethereal = gtk_button_new_with_label ("Ethereal");
    airsnort = gtk_button_new_with_label ("Airsnort");
    ettercap = gtk_button_new_with_label ("Ettercap");
    xfsamba = gtk_button_new_with_label ("XFSamba");
    kismet = gtk_button_new_with_label ("Kismet");
    nmapfe = gtk_button_new_with_label ("NMAPfe");
    driftnet = gtk_button_new_with_label ("Drift Net");
    urlsnarf = gtk_button_new_with_label ("URL Snarf");
    separator1 = gtk_hseparator_new ();    
    killsniffers = gtk_button_new_with_label ("Stop Sniffing");
    restartpcmcia = gtk_button_new_with_label ("Restart PCMCIA");
    killdhcp_bttn = gtk_button_new_with_label ("Kill DHCP Attempts");
    separator2 = gtk_hseparator_new ();
    ssidconfig = gtk_entry_new ();
    wlandevice = gtk_entry_new ();
    gtk_entry_set_text (GTK_ENTRY (ssidconfig), "linksys");
    gtk_entry_set_text (GTK_ENTRY (wlandevice), "wlan0");
    gtk_entry_set_max_length (GTK_ENTRY (ssidconfig), 14);
    gtk_entry_set_max_length (GTK_ENTRY (wlandevice), 5);
    wlanconfig_bttn = gtk_button_new_with_label ("Set SSID & Interface");
    separator3 = gtk_hseparator_new ();
    ifconfigip = gtk_entry_new ();   
    gtk_entry_set_text (GTK_ENTRY (ifconfigip), "192.168.1.117");
    gtk_entry_set_max_length (GTK_ENTRY (ifconfigip), 15);
    ifconfigip_bttn = gtk_button_new_with_label ("Set IP Address");
    dhcp_bttn = gtk_button_new_with_label ("Attempt DHCP");
    separator4 = gtk_hseparator_new ();
    adj1 = gtk_adjustment_new (255, 0, 256, 1, 5, 5);
    scrollbar = gtk_hscrollbar_new (GTK_ADJUSTMENT (adj1));
    gtk_range_set_update_policy (GTK_RANGE (scrollbar), GTK_UPDATE_CONTINUOUS);
    sonylabel = gtk_label_new ("Sony Backlight: Range 0-255, Increment of 1");
    separator5 = gtk_hseparator_new ();
    screenshot_bttn = gtk_button_new_with_label ("Screenshot");   
    log_bttn = gtk_button_new_with_label ("Edit Location Log");

/*Establish window title - Establish width of window - Create widgit table - Pack buttons in widgit table*/
    gtk_window_set_title (GTK_WINDOW (window1), "uncompiled.com Wardrive");    
    gtk_container_add (GTK_CONTAINER (window1), table);
    gtk_table_attach_defaults (GTK_TABLE (table), ethereal,        0, 1, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE (table), airsnort,        1, 2, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE (table), ettercap,        0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE (table), xfsamba,         1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE (table), kismet,          2, 3, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE (table), nmapfe,          2, 3, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE (table), driftnet,        0, 1, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE (table), urlsnarf,        1, 2, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE (table), separator1,      0, 3, 3, 4);
    gtk_table_attach_defaults (GTK_TABLE (table), killsniffers,    0, 1, 4, 5);   
    gtk_table_attach_defaults (GTK_TABLE (table), restartpcmcia,   1, 2, 4, 5);
    gtk_table_attach_defaults (GTK_TABLE (table), killdhcp_bttn,   2, 3, 4, 5);
    gtk_table_attach_defaults (GTK_TABLE (table), separator2,      0, 3, 5, 6);
    gtk_table_attach_defaults (GTK_TABLE (table), ssidconfig,      0, 1, 6, 7);
    gtk_table_attach_defaults (GTK_TABLE (table), wlandevice,      1, 2, 6, 7);
    gtk_table_attach_defaults (GTK_TABLE (table), wlanconfig_bttn, 2, 3, 6, 7);
    gtk_table_attach_defaults (GTK_TABLE (table), separator3,      0, 3, 7, 8);    
    gtk_table_attach_defaults (GTK_TABLE (table), ifconfigip,      0, 1, 8, 9);
    gtk_table_attach_defaults (GTK_TABLE (table), ifconfigip_bttn, 1, 2, 8, 9);
    gtk_table_attach_defaults (GTK_TABLE (table), dhcp_bttn,       2, 3, 8, 9);    
    gtk_table_attach_defaults (GTK_TABLE (table), separator4,      0, 3, 9, 10);
    gtk_table_attach_defaults (GTK_TABLE (table), scrollbar,       0, 1, 10, 11);
    gtk_table_attach_defaults (GTK_TABLE (table), sonylabel,       1, 3, 10, 11);
    gtk_table_attach_defaults (GTK_TABLE (table), separator5,      0, 3, 11, 12);
    gtk_table_attach_defaults (GTK_TABLE (table), screenshot_bttn, 0, 1, 12, 13);
    gtk_table_attach_defaults (GTK_TABLE (table), log_bttn,        1, 2, 12, 13);

/*Create signal calls for application (Destroying window, Calling programs, etc.)*/
    g_signal_connect (G_OBJECT (window1), "delete_event", G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (ethereal), "clicked", G_CALLBACK (call_ethereal), NULL);
    g_signal_connect (G_OBJECT (airsnort), "clicked", G_CALLBACK (call_airsnort), NULL);
    g_signal_connect (G_OBJECT (ettercap), "clicked", G_CALLBACK (call_ettercap), NULL);
    g_signal_connect (G_OBJECT (xfsamba), "clicked", G_CALLBACK (call_xfsamba), NULL);
    g_signal_connect (G_OBJECT (kismet), "clicked", G_CALLBACK (call_kismet), NULL);
    g_signal_connect (G_OBJECT (nmapfe), "clicked", G_CALLBACK (call_nmapfe), NULL);
    g_signal_connect (G_OBJECT (driftnet), "clicked", G_CALLBACK (call_driftnet), NULL);
    g_signal_connect (G_OBJECT (urlsnarf), "clicked", G_CALLBACK (call_urlsnarf), NULL);
    g_signal_connect (G_OBJECT (killsniffers), "clicked", G_CALLBACK (call_killsniffers), NULL);
    g_signal_connect (G_OBJECT (restartpcmcia), "clicked", G_CALLBACK (call_restartpcmcia), NULL);
    g_signal_connect (G_OBJECT (killdhcp_bttn), "clicked", G_CALLBACK (call_killdhcp), NULL);
    g_signal_connect (G_OBJECT (wlanconfig_bttn), "clicked", G_CALLBACK (call_ssidconfig), NULL);
    g_signal_connect (G_OBJECT (ifconfigip_bttn), "clicked", G_CALLBACK (call_ifconfigip), NULL);
    g_signal_connect (G_OBJECT (dhcp_bttn), "clicked", G_CALLBACK (call_dhcp), NULL);
    g_signal_connect (G_OBJECT (adj1), "value_changed", G_CALLBACK (call_scroll), NULL);
    g_signal_connect (G_OBJECT (screenshot_bttn), "clicked", G_CALLBACK (call_screenshot), NULL);
    g_signal_connect (G_OBJECT (log_bttn), "clicked", G_CALLBACK (call_log), NULL);

/*Add buttons, widgit box, and window to application*/
    gtk_widget_show (ethereal);
    gtk_widget_show (airsnort);
    gtk_widget_show (ettercap);
    gtk_widget_show (xfsamba);
    gtk_widget_show (kismet);
    gtk_widget_show (nmapfe);
    gtk_widget_show (driftnet);
    gtk_widget_show (urlsnarf);
    gtk_widget_show (table);
    gtk_widget_show (separator1);
    gtk_widget_show (killsniffers);
    gtk_widget_show (restartpcmcia);
    gtk_widget_show (killdhcp_bttn);
    gtk_widget_show (separator2); 
    gtk_widget_show (ssidconfig);
    gtk_widget_show (wlandevice);
    gtk_widget_show (wlanconfig_bttn);
    gtk_widget_show (separator3);
    gtk_widget_show (ifconfigip);
    gtk_widget_show (ifconfigip_bttn);
    gtk_widget_show (dhcp_bttn);
    gtk_widget_show (separator4);
    gtk_widget_show (scrollbar);
    gtk_widget_show (sonylabel);
    gtk_widget_show (separator5);
    gtk_widget_show (screenshot_bttn);
    gtk_widget_show (log_bttn);
    gtk_widget_show (window1);    

    gtk_main ();
    return 0;
}
