import * as $ from 'jquery'
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
    this.links = this.getFallbackApiLinksFromHiddenHtml()
  }

  getFallbackApiLinksFromHiddenHtml () {
    const navFallback = $('nav.fallback ul li a')
    let result: { url: string, text: string }[] = $.map(navFallback, link => {
      let $link = $(link)
      return {
        url: $link.attr('href'),
        text: $link.text()
      }
    })
    result.shift()
    return result
  }
}
