/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Arduino.h"
#include "wifi.h"

Wifi wifi;

void Wifi::begin(AwsEventHandler handler)
{
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  static AsyncWebServer server(WEBSERVER_PORT);
  this->beginWebServer(&server);
  static AsyncWebSocket ws(WEBSOCKET_PATH);
  ws.onEvent(handler);
  server.addHandler(&ws);
  server.begin();
  MDNS.begin(MDNS_DOMAIN_NAME);
}

void Wifi::beginWebServer(AsyncWebServer * server)
{
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", INDEX_HTML);
  });
}
