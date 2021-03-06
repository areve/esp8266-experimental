import { Injectable, Inject } from '@angular/core'
import { Http, RequestOptions, URLSearchParams } from '@angular/http'

const stop: string = '0,0,1,100000000'

@Injectable()
export class BotService {
  _http: Http
  _connection: WebSocket
  _listeners: Array<{(Object): void }> = []
  constructor( @Inject(Http) private http: Http) {
    this._http = http

    this._connection = new WebSocket('ws://' +
      document.location.hostname + ':81/', ['arduino'])
    this._connection.onopen = () => {
      console.log('Connected to WebSocket')
    }
    this._connection.onerror = (error) => {
      console.log('WebSocket error: ', error)
    }
    this._connection.onmessage = (e) => {
      for (let i = 0; i < this._listeners.length; i++) {
        this._listeners[i](JSON.parse(e.data))
      }

      if (!this._listeners.length) {
        console.log('Server said: ', e.data)
      }
    }
  }

  forwards() {
    return this.motor('1,8,0,1700,' + stop, '1,8,0,1700,' + stop)
  }

  backwards() {
    return this.motor('8,1,0,1700,' + stop, '8,1,0,1700,' + stop)
  }

  left() {
    return this.motor('8,1,0,1700,' + stop, '1,8,0,1700,' + stop)
  }

  right() {
    return this.motor('1,8,0,1700,' + stop, '8,1,0,1700,' + stop)
  }

  stop() {
    return this.motor(stop, stop)
  }

  startUltraSound() {
    return this._http.post('/api/us', this.toParams({
      enabled: 1,
      pinTrigger: 13,
      pinEcho: 15,
      logLevel: 0,
      interval: 50000
    }))
      .map(response => response.json() || {})
  }

  readUltraSound() {
    return this._http.get('/api/us')
      .map(response => response.json() || {})
  }

  requestUltraSound() {
    if (this._connection.readyState === 1)
      this._connection.send('GET /api/us')
  }

  private motor(pattern1: string, pattern2: string) {
    return this._http.post('/api/motor', this.toParams({
      enabled: 1,
      latchPin: 14,
      clockPin: 16,
      dataPin: 12,
      motors: 2,
      patternOptions0: pattern1,
      resetPosition0: 1,
      patternOptions1: pattern2,
      resetPosition1: 1
    }))
      .map(response => response.json() || {})
  }

  private toParams(object: Object): URLSearchParams {
    let params = new URLSearchParams()
    for (let key in object)
      params.set(key, object[key])
    return params
  }
}
