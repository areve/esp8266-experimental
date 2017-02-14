import { NgModule } from '@angular/core'
import { BrowserModule } from '@angular/platform-browser'
import { HttpModule } from '@angular/http'
import { ConfigComponent } from '../config/config.component'
import { MothComponent } from './moth.component'
import { FileSystemComponent } from '../file-system/file-system.component'
import { HomeComponent } from '../home/home.component'
import { RouterModule, Routes } from '@angular/router'


const appRoutes: Routes = [
  {
    path: 'home',
    component: HomeComponent
  },
  {
    path: 'filesystem',
    component: FileSystemComponent,
    data: { title: 'filesystem' }
  },
  {
    path: 'config',
    component: ConfigComponent,
    data: { title: 'config' }
  },
  {
    path: 'heroes/:id',
    component: ConfigComponent,
    data: { title: 'Heroes List' }
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
    RouterModule.forRoot(appRoutes)
  ],
  declarations: [
    MothComponent,
    HomeComponent,
    FileSystemComponent,
    ConfigComponent
  ],
  bootstrap: [MothComponent]
})
export class MothModule { }
