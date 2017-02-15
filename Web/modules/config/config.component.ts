import { Component, OnInit, Inject } from '@angular/core'
import { ConfigService } from './config.service'

@Component({
  providers: [ConfigService],
  template: `
    <div>
      <label>accessPointName
        <input type="text" required
        [(ngModel)]="config.accessPointName"></label>
    </div>
    <div>
      <label>accessPointPassphrase
        <input type="password" required
        [(ngModel)]="config.accessPointPassphrase"></label>
    </div>
    <div>
      <label>wifiSsid
        <input type="text" required
        [(ngModel)]="config.wifiSsid"></label>
    </div>
    <div>
      <label>wifiPassphrase
        <input type="password" required
        [(ngModel)]="config.wifiPassphrase"></label>
    </div>
    <div>
      <label>devScriptUrl
        <input type="text" required
        [(ngModel)]="config.devScriptUrl"></label>
    </div>
    <button (click)="save()">Save</button>
  `
})
export class ConfigComponent {
  config: Object
  private configService: ConfigService

  constructor ( @Inject(ConfigService) configService: ConfigService) {
    this.configService = configService;
    this.config = {}
    configService.read()
      .subscribe((config) => this.config = config, console.error)

  }

  save(){
    this.configService.save(this.config)
      .subscribe(console.log, console.error)

  }
}
