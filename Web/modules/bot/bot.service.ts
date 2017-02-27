import { Injectable, Inject } from '@angular/core'
import { Http, RequestOptions, URLSearchParams } from '@angular/http'

const stop:string = '24,24,1,100000000'

@Injectable()
export class BotService {
  _http: Http
  constructor ( @Inject(Http) private http: Http) {
    this._http = http
  }

  forwards () {
    return this.motor('0,7,80,50000,' + stop, '0,7,80,50000,' + stop)
  }

  backwards () {
    return this.motor('8,15,80,50000,' + stop, '8,15,80,50000,' + stop)
  }

  left () {
    return this.motor('8,15,80,50000,' + stop, '0,7,80,50000,' + stop)
  }

  right () {
    return this.motor('0,7,80,50000,' + stop, '8,15,80,50000,' + stop)
  }

  stop () {
    return this.motor(stop, stop)
  }

  private motor (pattern1:string, pattern2:string) {
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

  private toParams (object: Object): URLSearchParams {
    let params = new URLSearchParams()
    for (let key in object)
      params.set(key, object[key])
    return params
  }
}
