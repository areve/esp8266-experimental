import { Injectable, Inject } from '@angular/core'
import { Http, RequestOptions, URLSearchParams, Response } from '@angular/http'
// import 'rxjs/add/operator/map'
// import 'rxjs/add/operator/toPromise'

@Injectable()
export class BotService {
  _http: Http
  constructor ( @Inject(Http) private http: Http) {
    this._http = http
  }

  forwards () {
    return this.motor('0,7,160,50000', '0,7,160,50000')
  }

  backwards () {
    return this.motor('8,15,160,50000', '8,15,160,50000')
  }

  left () {
    return this.motor('8,15,160,50000', '0,7,160,50000')
  }

  right () {
    return this.motor('0,7,160,50000', '8,15,160,50000')
  }

  stop () {
    return this.motor('24,24,1,100000000', '24,24,1,100000000')
  }

  private motor (pattern1, pattern2) {
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
