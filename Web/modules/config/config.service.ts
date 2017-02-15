import { Injectable, Inject } from '@angular/core'
import { Http, RequestOptions, URLSearchParams, Response } from '@angular/http'
import 'rxjs/add/operator/map'
import 'rxjs/add/operator/toPromise'

@Injectable()
export class ConfigService {
  _http: Http
  constructor( @Inject(Http) private http: Http) {
    this._http = http
  }

  save(object: Object) {
    return this._http.post('/api/config', {}, new RequestOptions({
      search: this.toParams(object)
    }))
      .map(response => response.json() || {})
  }

  read() {
    return this._http.get('/api/config')
      .map(response => response.json() || {})
  }

  private toParams(object: Object): URLSearchParams {
    let params = new URLSearchParams()
    for (let key in object)
      params.set(key, object[key])
    return params
  }

  private extractData(res: Response) {
    return res.json() || {}
  }

  private handleError(error: Response | any) {
    console.error(error)
    return Promise.reject(error)
  }
}
