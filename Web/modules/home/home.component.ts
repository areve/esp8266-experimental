import { Component, OnInit, Inject } from '@angular/core'

@Component({
  template: `
    <section class="home">
      <h1>MOTH</h1>
      <p>A web site on a ESP8266, to control it.</p>

      <section class="api-links">
        <h1>API links</h1>
        <ul>
          <li *ngFor="let link of links"><a href="{{link.url}}">{{link.text}}</a></li>
        </ul>
      </section>
    </section>
  `
})
export class HomeComponent {
  links: { url: string, text: string }[]
  constructor () {
    this.links = [
     { url: '/api/pins', text: '/api/pins' },
     { url: '/api/stepper', text: '/api/stepper' },
      { url: '/api/ledmatrix', text: '/api/ledmatrix' },
      { url: '/api/us', text: '/api/us' },
      { url: '/api/motor', text: '/api/motor' },
      { url: '/api/fs', text: '/api/fs' },
      { url: '/api/config', text: '/api/config' }
    ]
  }
}
