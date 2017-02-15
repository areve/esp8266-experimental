import 'zone.js'
import 'reflect-metadata'
import { enableProdMode } from '@angular/core'
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic'
import { MothModule } from './moth.module'

window['scriptJs'] = 1

setTimeout(() => {
  if (document.getElementsByTagName('app').length) platformBrowserDynamic().bootstrapModule(MothModule)
}, 0)
