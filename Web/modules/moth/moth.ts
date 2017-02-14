import 'zone.js'
import 'reflect-metadata'
import { enableProdMode } from '@angular/core'
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic'
import { NgModule } from '@angular/core'
import { BrowserModule } from '@angular/platform-browser'
import { HttpModule } from '@angular/http'
import { ConfigComponent } from '../config/config.component'
import { MothComponent } from './moth.component'
import { MothModule } from './moth.module'

import * as $ from 'jquery'

window['scriptJs'] = 1

$(() => {
  platformBrowserDynamic().bootstrapModule(MothModule)
})
