import { NgModule } from '@angular/core'
import { BrowserModule } from '@angular/platform-browser'
import { HttpModule } from '@angular/http'
import { ConfigComponent } from '../config/config.component'
import { MothComponent } from './moth.component'
import { FileSystemComponent } from '../file-system/file-system.component'
import { BotComponent } from '../bot/bot.component'
import { HomeComponent } from '../home/home.component'
import { RouterModule, Routes } from '@angular/router'
import { FormsModule } from '@angular/forms'


const appRoutes: Routes = [
  {
    path: 'home',
    component: HomeComponent
  },
  {
    path: 'filesystem',
    component: FileSystemComponent
  },
  {
    path: 'config',
    component: ConfigComponent
  },
  {
    path: 'bot',
    component: BotComponent
  },
  {
    path: '',
    redirectTo: '/home',
    pathMatch: 'full'
  },
  { path: '**', component: HomeComponent }
]

@NgModule({
  imports: [
    BrowserModule,
    HttpModule,
    FormsModule,
    RouterModule.forRoot(appRoutes)
  ],
  declarations: [
    MothComponent,
    HomeComponent,
    BotComponent,
    FileSystemComponent,
    ConfigComponent
  ],
  bootstrap: [MothComponent]
})
export class MothModule { }
