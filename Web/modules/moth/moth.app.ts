import 'zone.js'
import 'reflect-metadata'
import { enableProdMode } from '@angular/core'
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic'
import { MothModule } from './moth.module'

import * as $ from 'jquery'

window['scriptJs'] = 1

$(() => {
  if ($('app').length) platformBrowserDynamic().bootstrapModule(MothModule)
})
