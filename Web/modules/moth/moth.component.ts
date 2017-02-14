import { Component, OnInit, Inject } from '@angular/core'

@Component({
  selector: 'app',
  template: `
  <nav>
    <ul>
      <li><a routerLink="/home" routerLinkActive="active">home</a></li>
      <li><a routerLink="/config" routerLinkActive="active">config</a></li>
      <li><a routerLink="/filesystem" routerLinkActive="active">filesystem</a></li>
    </ul>
  </nav>
  <router-outlet></router-outlet>
  `
})
export class MothComponent { }
