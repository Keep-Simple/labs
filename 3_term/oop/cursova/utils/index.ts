import { RcFile } from "antd/lib/upload"
import {
  Ticket,
  ticketsSerializer,
  ticketsValidator,
  TicketsValidatorReturnType,
} from "./schemas"
import { message, notification } from "antd"

export const capitalize = (s: any) => {
  if (typeof s !== "string") return ""
  return s.charAt(0).toUpperCase() + s.slice(1)
}

export function mostUsedTicket(tickets: Ticket[]) {
  const stats = {}
  let mostUsed = null
  for (let ticket of tickets) {
    stats[ticket.ticketType] ??= 0
    stats[ticket.ticketType] += 1

    if (mostUsed == null) {
      mostUsed = ticket.ticketType
    } else {
      mostUsed =
        stats[ticket.ticketType] > stats[mostUsed]
          ? ticket.ticketType
          : mostUsed
    }
  }

  if (mostUsed == null) {
    return null
  }

  return {
    ticketType: mostUsed,
    count: stats[mostUsed],
  } as const
}

class TicketsPersister {
  generateDownloadLink(tickets: Ticket[]) {
    if (!tickets.length) return

    const raw = ticketsSerializer(tickets)
    return URL.createObjectURL(
      new Blob([raw], {
        type: "application/json",
      })
    )
  }

  loadFromFile(file: RcFile, onLoad: (tickets: Ticket[]) => void) {
    const reader = new FileReader()
    reader.readAsText(file)
    reader.onload = () => {
      const raw = reader.result?.toString() || "[]"
      let tickets: Ticket[] = []
      let errors: TicketsValidatorReturnType = []

      try {
        tickets = JSON.parse(raw)
      } catch (e) {
        if (e instanceof Error) {
          errors.push({
            message: `File is corrupted (wrong json)`,
            meta: e.message,
          })
        }
      }
      errors.push(...ticketsValidator(tickets))

      if (errors?.length) {
        errors.forEach((e) =>
          notification.error({
            message: `${e.message}`,
            description: `Please fix the detected error: ${e.meta}`,
            placement: "bottomLeft",
            duration: 30,
          })
        )
      }

      if (tickets.length) {
        onLoad(tickets)
        message.success(`Loaded tickets from ${file.name}`)
      } else {
        message.info(`File ${file.name} was emtpy`)
      }
    }
  }
}

export const ticketsPersistor = new TicketsPersister()
