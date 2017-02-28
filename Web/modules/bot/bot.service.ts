import { Injectable, Inject } from '@angular/core'
import { Http, RequestOptions, URLSearchParams } from '@angular/http'

const stop:string = '0,0,1,100000000'

@Injectable()
export class BotService {
  _http: Http
  constructor ( @Inject(Http) private http: Http) {
    this._http = http
  }

  forwards () {
    return this.motor('1,8,80,200000,' + stop, '1,8,80,200000,' + stop)
  }

  backwards () {
    return this.motor('9,16,80,200000,' + stop, '9,16,80,200000,' + stop)
  }

  left () {
    return this.motor('9,16,80,200000,' + stop, '1,8,80,200000,' + stop)
  }

  right () {
    return this.motor('1,8,80,200000,' + stop, '9,16,80,200000,' + stop)
  }

  stop () {
    return this.motor(stop, stop)
  }

  startUltraSound () {
    return this._http.post('/api/us', this.toParams({
      enabled: 1,
      pinTrigger: 13,
      pinEcho: 15,
      logLevel: 0,
      interval: 50000
    }))
      .map(response => response.json() || {})
  }

  readUltraSound () {
    return this._http.get('/api/us')
      .map(response => response.json() || {})
  }

  private motor (pattern1:string, pattern2:string) {
    return this._http.post('/api/motor', this.toParams({
      enabled: 1,
      latchPin: 14,
      clockPin: 16,
      dataPin: 12,
      motors: 4,
      patternOptions0: pattern1,
      resetPosition0: 1,
      patternOptions1: pattern2,
      resetPosition1: 1,
      patternOptions2: stop,
      resetPosition2: 1,
      patternOptions3: stop,
      resetPosition3: 1
    }))
      .map(response => response.json() || {})
  }

  private toParams (object: Object): URLSearchParams {
    let params = new URLSearchParams()
    for (let key in object)
      params.set(key, object[key])
    return params
  }
}
