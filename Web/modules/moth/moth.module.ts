import { NgModule } from '@angular/core'
import { BrowserModule } from '@angular/platform-browser'
import { HttpModule } from '@angular/http'
import { ConfigComponent } from '../config/config.component'
import { MothComponent } from './moth.component'

@NgModule({
  imports: [
    BrowserModule,
    HttpModule
  ],
  declarations: [
    MothComponent,
    ConfigComponent
  ],
  bootstrap: [MothComponent]
})
export class MothModule { }
